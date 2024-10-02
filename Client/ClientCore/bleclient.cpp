#include "bleclient.h"

BLEClient::BLEClient(QObject *parent) :
    QObject(parent)
{
    // Ensure Bluetooth is powered on
    localDevice.powerOn();

    // New QPermission system
    qApp->requestPermission(QBluetoothPermission(), [](const QPermission &permission) {
        if (permission.status() == Qt::PermissionStatus::Granted) {
            qDebug() << "Bluetooth permission granted";
            // Add your Bluetooth initialization code here
        } else {
            qDebug() << "Bluetooth permission denied";
            // Handle the permission denial
        }
    });

    // DiscoveryAgent for doscovering BLE server
    agent = new QBluetoothDeviceDiscoveryAgent;
    connect(agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BLEClient::agentDeviceDiscovered);
    connect(agent, &QBluetoothDeviceDiscoveryAgent::errorOccurred, this, &BLEClient::agentError);
    connect(agent, &QBluetoothDeviceDiscoveryAgent::finished, this, &BLEClient::agentFinished);
    connect(agent, &QBluetoothDeviceDiscoveryAgent::canceled, this, &BLEClient::agentCanceled);
}


// Agent connected methods

void BLEClient::agentError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    qDebug() << "Device discovery error: " << error;
}

void BLEClient::agentFinished()
{
    qDebug() << "Device discovery finished.";
}

void BLEClient::agentCanceled()
{
    qDebug() << "Device discovery canceled.";
}

void BLEClient::agentDeviceDiscovered(const QBluetoothDeviceInfo &info)
{
    if(serverName.isEmpty()) {
        qDebug() << "Server discovered: " << info.name();
        emit sigServerFound(info.name());
    } else if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration && serverName == info.name()) {
        qDebug() << "Server " << info.name() << info.address().toString() << " found try to connect!";
        // create controller
        controller = QLowEnergyController::createCentral(info);
        connect(controller, &QLowEnergyController::serviceDiscovered, this, &BLEClient::controllerDiscovered);
        connect(controller, &QLowEnergyController::discoveryFinished, this, &BLEClient::controllerFinished);
        connect(controller, &QLowEnergyController::errorOccurred, this, &BLEClient::controllerError);
        connect(controller, &QLowEnergyController::connected, this, &BLEClient::controllerConnected);
        connect(controller, &QLowEnergyController::disconnected, this, &BLEClient::controllerDisconnected);
        controller->connectToDevice();
    }
}


            // Controller connections
void BLEClient::controllerFinished()
{
    qDebug() << "controllerFinished()";
}

void BLEClient::controllerError(QLowEnergyController::Error newError)
{
    qDebug() << "controllerError(): " << newError;
}

void BLEClient::controllerConnected()
{
    emit sigConnected(serverName);
    qDebug() << "controllerConnected()";
}

void BLEClient::controllerDisconnected()
{
    qDebug() << "controllerDisconnected()";
}

void BLEClient::controllerDiscovered(const QBluetoothUuid &newService)
{
    if (serviceUuid == newService)
        service = controller->createServiceObject(serviceUuid, this);

    if (service) {
        connect(service, &QLowEnergyService::stateChanged, this, &BLEClient::serviceStateChanged);
        connect(service, &QLowEnergyService::characteristicChanged, this, &BLEClient::serviceCharChanged);
        connect(service, &QLowEnergyService::descriptorWritten, this, &BLEClient::serviceDescWritten);
        service->discoverDetails();
    } else {
        qDebug() << "Heart Rate Service not found.";
    }
}


            // Service connections

// The state of the service changed
void BLEClient::serviceStateChanged(QLowEnergyService::ServiceState newState)
{
    if (newState == QLowEnergyService::RemoteServiceDiscovered) {
        characteristic = service->characteristic(characteristicUuid);
        if (characteristic.isValid()) {
            service->readCharacteristic(characteristic);
        }
    }
}

// Data received from the service
void BLEClient::serviceCharChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue)
{
    if (characteristic.uuid() == characteristicUuid) {
        QVariant data = QVariant::fromValue(newValue);
        emit sigDataReceived(data);
    }
}

void BLEClient::serviceDescWritten(const QLowEnergyDescriptor &descriptor, const QByteArray &newValue)
{
    qDebug() << "serviceDescWritten()";
}


void BLEClient::sendData(QVariant &value)
{
    if (service && characteristic.isValid()) {
        QByteArray byteValue = value.toByteArray();
        service->writeCharacteristic(characteristic, byteValue);
    }
}

void BLEClient::searchServer()
{
    if(!agent->isActive()) {
        qDebug() << "Searching for servers";
        this->serverName.clear();
        agent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    }
}

void BLEClient::connectToServer(QString serverName)
{
    if(!agent->isActive()) {
        qDebug() << "Searching for server: " << serverName;
        this->serverName = serverName;
        agent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    }
}




