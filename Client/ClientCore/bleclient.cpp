#include "bleclient.h"
#include <QDebug>

BleClient::BleClient(QObject *parent, EventBus *eventBus)
    : QObject(parent),
    deviceDiscoveryAgent(nullptr),
    energyController(nullptr),
    energyService(nullptr)
{
    // Assign the eventBus
    this->eventBus = eventBus;

    // Get logger instance
    this->logger = Logger::getInstance();

    // Initialize the device discovery agent
    deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(5000); // 5 seconds timeout

    // Connect signals to slots
    connect(deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this,                   &BleClient::deviceDiscoveryDeviceDiscovered);
    connect(deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this,                   &BleClient::deviceDiscoveryFinished);
    connect(deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
            this,                   &BleClient::deviceDiscoveryError);
}

BleClient::~BleClient()
{
    if (energyController) {
        energyController->disconnectFromDevice();
        delete energyController;
    }
}

void BleClient::setTargetDeviceName(const QString &name)
{
    targetDeviceName = name;
}

void BleClient::startDeviceDiscovery()
{
    deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BleClient::deviceDiscoveryDeviceDiscovered(const QBluetoothDeviceInfo &deviceInfo)
{
    // Check if the device supports BLE and matches the target name
    if (deviceInfo.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        if (deviceInfo.name() == targetDeviceName) {
            // Found the target device

            QVariantMap map;
            BluetoothUtils::deviceInfoToVariantMap(deviceInfo);

            emit eventBus->bleClientDeviceFound(map);
            logger->logInfo("Device found: " + deviceInfo.name());

            // Stop discovery
            deviceDiscoveryAgent->stop();

            // Connect to the device
            if (energyController) {
                energyController->disconnectFromDevice();
                delete energyController;
                energyController = nullptr;
            }

            // Create a controller for the device
            energyController = QLowEnergyController::createCentral(deviceInfo, this);
            connect(energyController, &QLowEnergyController::connected, this, &BleClient::controllerConnected);
            connect(energyController, &QLowEnergyController::disconnected, this, &BleClient::controllerDisconnected);
            connect(energyController, &QLowEnergyController::errorOccurred, this, &BleClient::controllerErrorOccurred);
            connect(energyController, &QLowEnergyController::serviceDiscovered, this, &BleClient::serviceDiscoveredHandler);
            connect(energyController, &QLowEnergyController::discoveryFinished, this, &BleClient::serviceScanDone);

            // Connect to the device
            energyController->connectToDevice();
        }
    }
}

void BleClient::deviceDiscoveryFinished()
{
    QVariantList list;
    for (const auto &deviceInfo : deviceDiscoveryAgent->discoveredDevices()) {
        QVariantMap map = BluetoothUtils::deviceInfoToVariantMap(deviceInfo);
        list.append(map);
    }
    emit eventBus->bleClientDiscoveryFinished(list);
    logger->logInfo("Device discovery finished.");
}

void BleClient::controllerConnected()
{
    QVariantMap map;
    emit eventBus->bleClientConnected(map);
    logger->logInfo("Client connected");
    // Start discovering services
    energyController->discoverServices();
}

void BleClient::controllerDisconnected()
{
    QVariantMap map;
    emit eventBus->bleClientDisconnected(map);
    logger->logInfo("Client disconnected");
}

void BleClient::controllerErrorOccurred(QLowEnergyController::Error errorMessage)
{
    QVariantMap map;
    map["Error Message"] = errorMessage;
    emit eventBus->bleClientError(map);
    logger->logError(energyController->errorString());
}

void BleClient::serviceDiscoveredHandler(const QBluetoothUuid &serviceUuid)
{
    // For this example, we assume the first service is the one we want
    Q_UNUSED(serviceUuid);
}

void BleClient::serviceScanDone()
{
    // For simplicity, connect to the first service
    QList<QBluetoothUuid> services = energyController->services();
    if (!services.isEmpty()) {
        QBluetoothUuid serviceUuid = services.first();

        if (energyService)
            delete energyService;
        energyService = energyController->createServiceObject(serviceUuid, this);
        if (energyService) {
            connect(energyService, &QLowEnergyService::stateChanged, this, &BleClient::serviceStateChanged);
            connect(energyService, &QLowEnergyService::characteristicChanged, this, &BleClient::dataReceived);
            connect(energyService, &QLowEnergyService::descriptorWritten, this, &BleClient::descriptorWritten);

            // Discover service details
            energyService->discoverDetails();
        } else {
            QVariantMap map;
            emit eventBus->bleClientError(map);
            logger->logError("Failed to create service object");
        }
    } else {
        QVariantMap map;
        emit eventBus->bleClientError(map);
        logger->logError("No services found");
    }
}

void BleClient::serviceStateChanged(QLowEnergyService::ServiceState s)
{
    if (s == QLowEnergyService::RemoteServiceDiscovered) {
        // Service details have been discovered

        // Search for characteristics with write and notify properties
        const QList<QLowEnergyCharacteristic> chars = energyService->characteristics();

        for (const QLowEnergyCharacteristic &ch : chars) {
            if (ch.properties() & QLowEnergyCharacteristic::WriteNoResponse ||
                ch.properties() & QLowEnergyCharacteristic::Write) {
                sendData = ch;
            }
            if (ch.properties() & QLowEnergyCharacteristic::Notify ||
                ch.properties() & QLowEnergyCharacteristic::Indicate) {
                readCharacteristic = ch;

                // Enable notifications
                QBluetoothUuid cccdUuid(quint16(0x2902));
                notificationDesc = readCharacteristic.descriptor(cccdUuid);
                if (notificationDesc.isValid()) {
                    energyService->writeDescriptor(notificationDesc, QByteArray::fromHex("0100"));
                }
            }
        }

        if (!writeCharacteristic.isValid()) {
            QVariantMap map;
            emit eventBus->bleClientError(map);
            logger->logError("Write characteristic not found");
        }
        if (!readCharacteristic.isValid()) {
            QVariantMap map;
            emit eventBus->bleClientError(map);
            logger->logError("Read characteristic not found");
        }
    }
}

void BleClient::dataReceived(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
    if (c == readCharacteristic) {
        QVariantMap map;
        map["data"] = value;
        emit eventBus->bleClientDataReceived(map);
    }
}

void BleClient::descriptorWritten(const QLowEnergyDescriptor &d, const QByteArray &value)
{
    Q_UNUSED(value);
    if (d == notificationDesc) {
        // Notifications have been enabled
        qDebug() << "Notifications enabled for" << d.characteristic().uuid();
    }
}

void BleClient::sendData(const QByteArray &data)
{
    if (energyService && writeCharacteristic.isValid()) {
        energyService->writeCharacteristic(sendData, data);
    } else {
        QString message = "Cannot write to characteristic";
        QVariantMap map;
        map["message"] = message;
        emit eventBus->bleClientError(map);
        logger->logError(message);
    }
}

void BleClient::disconnectFromDevice()
{
    if (energyController) {
        energyController->disconnectFromDevice();
        delete energyController;
        energyController = nullptr;
    }
}
