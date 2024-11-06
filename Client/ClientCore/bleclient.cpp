#include "bleclient.h"
#include <QDebug>

BleClient::BleClient(QObject *parent, EventBus *eventBus)
    : QObject(parent),
    m_deviceDiscoveryAgent(nullptr),
    m_control(nullptr),
    m_service(nullptr)
{
    // Assign the eventBus
    this->eventBus = eventBus;

    // Get logger instance
    this->logger = Logger::getInstance();

    // Initialize the device discovery agent
    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(5000); // 5 seconds timeout

    // Connect signals to slots
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this,                   &BleClient::deviceDiscoveryDeviceDiscovered);
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this,                   &BleClient::deviceDiscoveryFinished);
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
            this,                   &BleClient::deviceDiscoveryError);
}

BleClient::~BleClient()
{
    if (m_control) {
        m_control->disconnectFromDevice();
        delete m_control;
    }
}

void BleClient::setTargetDeviceName(const QString &name)
{
    m_targetDeviceName = name;
}

void BleClient::startDeviceDiscovery()
{
    m_deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BleClient::deviceDiscoveryDeviceDiscovered(const QBluetoothDeviceInfo &deviceInfo)
{
    // Check if the device supports BLE and matches the target name
    if (deviceInfo.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        if (deviceInfo.name() == m_targetDeviceName) {
            // Found the target device

            QVariantMap map;
            map["deviceName"]               = deviceInfo.name();
            map["deviceAddress"]            = deviceInfo.address().toString();
            map["deviceUUID"]               = deviceInfo.deviceUuid();
            map["deviceCoreConfiguration"]  = BluetoothUtils::coreConfigurationToString(deviceInfo.coreConfigurations());

            emit eventBus->bleClientDeviceFound(map);
            logger->logInfo("Device found: " + deviceInfo.name());

            // Stop discovery
            m_deviceDiscoveryAgent->stop();

            // Connect to the device
            if (m_control) {
                m_control->disconnectFromDevice();
                delete m_control;
                m_control = nullptr;
            }

            // Create a controller for the device
            m_control = QLowEnergyController::createCentral(deviceInfo, this);
            connect(m_control, &QLowEnergyController::connected, this, &BleClient::controllerConnected);
            connect(m_control, &QLowEnergyController::disconnected, this, &BleClient::controllerDisconnected);
            connect(m_control, &QLowEnergyController::errorOccurred, this, &BleClient::controllerErrorOccurred);
            connect(m_control, &QLowEnergyController::serviceDiscovered, this, &BleClient::serviceDiscoveredHandler);
            connect(m_control, &QLowEnergyController::discoveryFinished, this, &BleClient::serviceScanDone);

            // Connect to the device
            m_control->connectToDevice();
        }
    }
}

void BleClient::deviceDiscoveryFinished()
{
    QVariantMap map;

    map["deviceName"]   = m_deviceDiscoveryAgent->;

    emit eventBus->bleClientDiscoveryFinished();
    logger->logInfo("Device discovery finished.");
}

void BleClient::controllerConnected()
{
    emit eventBus->bleClientConnected();
    logger->logInfo("Client connected");
    // Start discovering services
    m_control->discoverServices();
}

void BleClient::controllerDisconnected()
{
    emit eventBus->bleClientDisconnected();
    logger->logInfo("Client disconnected");
}

void BleClient::controllerErrorOccurred(QLowEnergyController::Error)
{
    emit eventBus->bleClientError();
    logger->logError(m_control->errorString());
}

void BleClient::serviceDiscoveredHandler(const QBluetoothUuid &serviceUuid)
{
    // For this example, we assume the first service is the one we want
    Q_UNUSED(serviceUuid);
}

void BleClient::serviceScanDone()
{
    // For simplicity, connect to the first service
    QList<QBluetoothUuid> services = m_control->services();
    if (!services.isEmpty()) {
        QBluetoothUuid serviceUuid = services.first();

        if (m_service)
            delete m_service;
        m_service = m_control->createServiceObject(serviceUuid, this);
        if (m_service) {
            connect(m_service, &QLowEnergyService::stateChanged, this, &BleClient::serviceStateChanged);
            connect(m_service, &QLowEnergyService::characteristicChanged, this, &BleClient::characteristicChanged);
            connect(m_service, &QLowEnergyService::descriptorWritten, this, &BleClient::descriptorWritten);

            // Discover service details
            m_service->discoverDetails();
        } else {
            emit errorOccurred("Failed to create service object");
            logger->logError("Failed to create service object");
        }
    } else {
        emit errorOccurred("No services found");
        logger->logError("No services found");
    }
}

void BleClient::serviceStateChanged(QLowEnergyService::ServiceState s)
{
    if (s == QLowEnergyService::RemoteServiceDiscovered) {
        // Service details have been discovered

        // Search for characteristics with write and notify properties
        const QList<QLowEnergyCharacteristic> chars = m_service->characteristics();

        for (const QLowEnergyCharacteristic &ch : chars) {
            if (ch.properties() & QLowEnergyCharacteristic::WriteNoResponse ||
                ch.properties() & QLowEnergyCharacteristic::Write) {
                m_writeCharacteristic = ch;
            }
            if (ch.properties() & QLowEnergyCharacteristic::Notify ||
                ch.properties() & QLowEnergyCharacteristic::Indicate) {
                m_readCharacteristic = ch;

                // Enable notifications
                m_notificationDesc = m_readCharacteristic.descriptor(
                    QBluetoothUuid::ClientCharacteristicConfiguration);
                if (m_notificationDesc.isValid()) {
                    m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));
                }
            }
        }

        if (!m_writeCharacteristic.isValid()) {
            emit errorOccurred("Write characteristic not found");
            logger->logError("Write characteristic not found");
        }
        if (!m_readCharacteristic.isValid()) {
            emit errorOccurred("Read characteristic not found");
            logger->logError("Read characteristic not found");
        }
    }
}

void BleClient::characteristicChanged(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
    if (c == m_readCharacteristic) {
        // emit dataReceived(value);
        emit eventBus->bleClientDataReceived();
    }
}

void BleClient::descriptorWritten(const QLowEnergyDescriptor &d, const QByteArray &value)
{
    Q_UNUSED(value);
    if (d == m_notificationDesc) {
        // Notifications have been enabled
        qDebug() << "Notifications enabled for" << d.characteristic().uuid();
    }
}

void BleClient::writeCharacteristic(const QByteArray &data)
{
    if (m_service && m_writeCharacteristic.isValid()) {
        m_service->writeCharacteristic(m_writeCharacteristic, data);
    } else {
        emit errorOccurred("Cannot write to characteristic");
        logger->logError("Cannot write to characteristic");
    }
}

void BleClient::disconnectFromDevice()
{
    if (m_control) {
        m_control->disconnectFromDevice();
        delete m_control;
        m_control = nullptr;
    }
}


// 1. CoreConfiguration Mapping
QString coreConfigurationToString(QBluetoothDeviceInfo::CoreConfigurations config) {
    switch (config) {
    case QBluetoothDeviceInfo::UnknownCoreConfiguration: return "UnknownCoreConfiguration";
    case QBluetoothDeviceInfo::BaseRateCoreConfiguration: return "BaseRateCoreConfiguration";
    case QBluetoothDeviceInfo::BaseRateAndLowEnergyCoreConfiguration: return "BaseRateAndLowEnergyCoreConfiguration";
    case QBluetoothDeviceInfo::LowEnergyCoreConfiguration: return "LowEnergyCoreConfiguration";
    default: return "Unknown";
    }
}

// 2. Field Mapping
QString fieldToString(QBluetoothDeviceInfo::Fields field) {
    switch (field) {
    case QBluetoothDeviceInfo::Field::None: return "None";
    case QBluetoothDeviceInfo::Field::RSSI: return "RSSI";
    case QBluetoothDeviceInfo::Field::ManufacturerData: return "ManufacturerData";
    case QBluetoothDeviceInfo::Field::ServiceData: return "ServiceData";
    case QBluetoothDeviceInfo::Field::All: return "All";
    default: return "Unknown";
    }
}

// 3. MajorDeviceClass Mapping
QString majorDeviceClassToString(QBluetoothDeviceInfo::MajorDeviceClass deviceClass) {
    switch (deviceClass) {
    case QBluetoothDeviceInfo::MiscellaneousDevice: return "MiscellaneousDevice";
    case QBluetoothDeviceInfo::ComputerDevice: return "ComputerDevice";
    case QBluetoothDeviceInfo::PhoneDevice: return "PhoneDevice";
    case QBluetoothDeviceInfo::NetworkDevice: return "NetworkDevice";
    case QBluetoothDeviceInfo::AudioVideoDevice: return "AudioVideoDevice";
    case QBluetoothDeviceInfo::PeripheralDevice: return "PeripheralDevice";
    case QBluetoothDeviceInfo::ImagingDevice: return "ImagingDevice";
    case QBluetoothDeviceInfo::WearableDevice: return "WearableDevice";
    case QBluetoothDeviceInfo::ToyDevice: return "ToyDevice";
    case QBluetoothDeviceInfo::HealthDevice: return "HealthDevice";
    case QBluetoothDeviceInfo::UncategorizedDevice: return "UncategorizedDevice";
    default: return "Unknown";
    }
}

// 4. MinorAudioVideoClass Mapping
QString minorAudioVideoClassToString(QBluetoothDeviceInfo::MinorAudioVideoClass avClass) {
    switch (avClass) {
    case QBluetoothDeviceInfo::UncategorizedAudioVideoDevice: return "UncategorizedAudioVideoDevice";
    case QBluetoothDeviceInfo::WearableHeadsetDevice: return "WearableHeadsetDevice";
    case QBluetoothDeviceInfo::HandsFreeDevice: return "HandsFreeDevice";
    case QBluetoothDeviceInfo::Microphone: return "Microphone";
    case QBluetoothDeviceInfo::Loudspeaker: return "Loudspeaker";
    case QBluetoothDeviceInfo::Headphones: return "Headphones";
    case QBluetoothDeviceInfo::PortableAudioDevice: return "PortableAudioDevice";
    case QBluetoothDeviceInfo::CarAudio: return "CarAudio";
    case QBluetoothDeviceInfo::SetTopBox: return "SetTopBox";
    case QBluetoothDeviceInfo::HiFiAudioDevice: return "HiFiAudioDevice";
    case QBluetoothDeviceInfo::Vcr: return "Vcr";
    case QBluetoothDeviceInfo::VideoCamera: return "VideoCamera";
    case QBluetoothDeviceInfo::Camcorder: return "Camcorder";
    case QBluetoothDeviceInfo::VideoMonitor: return "VideoMonitor";
    case QBluetoothDeviceInfo::VideoDisplayAndLoudspeaker: return "VideoDisplayAndLoudspeaker";
    case QBluetoothDeviceInfo::VideoConferencing: return "VideoConferencing";
    case QBluetoothDeviceInfo::GamingDevice: return "GamingDevice";
    default: return "Unknown";
    }
}

// 5. MinorComputerClass Mapping
QString minorComputerClassToString(QBluetoothDeviceInfo::MinorComputerClass computerClass) {
    switch (computerClass) {
    case QBluetoothDeviceInfo::UncategorizedComputer: return "UncategorizedComputer";
    case QBluetoothDeviceInfo::DesktopComputer: return "DesktopComputer";
    case QBluetoothDeviceInfo::ServerComputer: return "ServerComputer";
    case QBluetoothDeviceInfo::LaptopComputer: return "LaptopComputer";
    case QBluetoothDeviceInfo::HandheldClamShellComputer: return "HandheldClamShellComputer";
    case QBluetoothDeviceInfo::HandheldComputer: return "HandheldComputer";
    case QBluetoothDeviceInfo::WearableComputer: return "WearableComputer";
    default: return "Unknown";
    }
}

// 6. MinorHealthClass Mapping
QString minorHealthClassToString(QBluetoothDeviceInfo::MinorHealthClass healthClass) {
    switch (healthClass) {
    case QBluetoothDeviceInfo::UncategorizedHealthDevice: return "UncategorizedHealthDevice";
    case QBluetoothDeviceInfo::HealthBloodPressureMonitor: return "HealthBloodPressureMonitor";
    case QBluetoothDeviceInfo::HealthThermometer: return "HealthThermometer";
    case QBluetoothDeviceInfo::HealthWeightScale: return "HealthWeightScale";
    case QBluetoothDeviceInfo::HealthGlucoseMeter: return "HealthGlucoseMeter";
    case QBluetoothDeviceInfo::HealthPulseOximeter: return "HealthPulseOximeter";
    case QBluetoothDeviceInfo::HealthDataDisplay: return "HealthDataDisplay";
    case QBluetoothDeviceInfo::HealthStepCounter: return "HealthStepCounter";
    default: return "Unknown";
    }
}

// 7. MinorImagingClass Mapping
QString minorImagingClassToString(QBluetoothDeviceInfo::MinorImagingClass imagingClass) {
    switch (imagingClass) {
    case QBluetoothDeviceInfo::UncategorizedImagingDevice: return "UncategorizedImagingDevice";
    case QBluetoothDeviceInfo::ImageDisplay: return "ImageDisplay";
    case QBluetoothDeviceInfo::ImageCamera: return "ImageCamera";
    case QBluetoothDeviceInfo::ImageScanner: return "ImageScanner";
    case QBluetoothDeviceInfo::ImagePrinter: return "ImagePrinter";
    default: return "Unknown";
    }
}

// 8. MinorMiscellaneousClass Mapping
QString minorMiscellaneousClassToString(QBluetoothDeviceInfo::MinorMiscellaneousClass miscClass) {
    switch (miscClass) {
    case QBluetoothDeviceInfo::UncategorizedMiscellaneous: return "UncategorizedMiscellaneous";
    default: return "Unknown";
    }
}

// 9. MinorNetworkClass Mapping
QString minorNetworkClassToString(QBluetoothDeviceInfo::MinorNetworkClass networkClass) {
    switch (networkClass) {
    case QBluetoothDeviceInfo::NetworkFullService: return "NetworkFullService";
    case QBluetoothDeviceInfo::NetworkLoadFactorOne: return "NetworkLoadFactorOne";
    case QBluetoothDeviceInfo::NetworkLoadFactorTwo: return "NetworkLoadFactorTwo";
    case QBluetoothDeviceInfo::NetworkLoadFactorThree: return "NetworkLoadFactorThree";
    case QBluetoothDeviceInfo::NetworkLoadFactorFour: return "NetworkLoadFactorFour";
    case QBluetoothDeviceInfo::NetworkLoadFactorFive: return "NetworkLoadFactorFive";
    case QBluetoothDeviceInfo::NetworkLoadFactorSix: return "NetworkLoadFactorSix";
    case QBluetoothDeviceInfo::NetworkNoService: return "NetworkNoService";
    default: return "Unknown";
    }
}

// 10. MinorPeripheralClass Mapping
QString minorPeripheralClassToString(QBluetoothDeviceInfo::MinorPeripheralClass peripheralClass) {
    switch (peripheralClass) {
    case QBluetoothDeviceInfo::UncategorizedPeripheral: return "UncategorizedPeripheral";
    case QBluetoothDeviceInfo::KeyboardPeripheral: return "KeyboardPeripheral";
    case QBluetoothDeviceInfo::PointingDevicePeripheral: return "PointingDevicePeripheral";
    case QBluetoothDeviceInfo::KeyboardWithPointingDevicePeripheral: return "KeyboardWithPointingDevicePeripheral";
    case QBluetoothDeviceInfo::JoystickPeripheral: return "JoystickPeripheral";
    case QBluetoothDeviceInfo::GamepadPeripheral: return "GamepadPeripheral";
    case QBluetoothDeviceInfo::RemoteControlPeripheral: return "RemoteControlPeripheral";
    case QBluetoothDeviceInfo::SensingDevicePeripheral: return "SensingDevicePeripheral";
    case QBluetoothDeviceInfo::DigitizerTabletPeripheral: return "DigitizerTabletPeripheral";
    case QBluetoothDeviceInfo::CardReaderPeripheral: return "CardReaderPeripheral";
    default: return "Unknown";
    }
}

// 11. MinorPhoneClass Mapping
QString minorPhoneClassToString(QBluetoothDeviceInfo::MinorPhoneClass phoneClass) {
    switch (phoneClass) {
    case QBluetoothDeviceInfo::UncategorizedPhone: return "UncategorizedPhone";
    case QBluetoothDeviceInfo::CellularPhone: return "CellularPhone";
    case QBluetoothDeviceInfo::CordlessPhone: return "CordlessPhone";
    case QBluetoothDeviceInfo::SmartPhone: return "SmartPhone";
    case QBluetoothDeviceInfo::WiredModemOrVoiceGatewayPhone: return "WiredModemOrVoiceGatewayPhone";
    case QBluetoothDeviceInfo::CommonIsdnAccessPhone: return "CommonIsdnAccessPhone";
    default: return "Unknown";
    }
}

// 12. MinorToyClass Mapping
QString minorToyClassToString(QBluetoothDeviceInfo::MinorToyClass toyClass) {
    switch (toyClass) {
    case QBluetoothDeviceInfo::UncategorizedToy: return "UncategorizedToy";
    case QBluetoothDeviceInfo::ToyRobot: return "ToyRobot";
    case QBluetoothDeviceInfo::ToyVehicle: return "ToyVehicle";
    case QBluetoothDeviceInfo::ToyDoll: return "ToyDoll";
    case QBluetoothDeviceInfo::ToyController: return "ToyController";
    case QBluetoothDeviceInfo::ToyGame: return "ToyGame";
    default: return "Unknown";
    }
}

// 13. MinorWearableClass Mapping
QString minorWearableClassToString(QBluetoothDeviceInfo::MinorWearableClass wearableClass) {
    switch (wearableClass) {
    case QBluetoothDeviceInfo::UncategorizedWearableDevice: return "UncategorizedWearableDevice";
    case QBluetoothDeviceInfo::WearableWristWatch: return "WearableWristWatch";
    case QBluetoothDeviceInfo::WearablePager: return "WearablePager";
    case QBluetoothDeviceInfo::WearableJacket: return "WearableJacket";
    case QBluetoothDeviceInfo::WearableHelmet: return "WearableHelmet";
    case QBluetoothDeviceInfo::WearableGlasses: return "WearableGlasses";
    default: return "Unknown";
    }
}

// 14. ServiceClass Mapping
QString serviceClassToString(QBluetoothDeviceInfo::ServiceClasses serviceClass) {
    switch (serviceClass) {
    case QBluetoothDeviceInfo::NoService: return "NoService";
    case QBluetoothDeviceInfo::PositioningService: return "PositioningService";
    case QBluetoothDeviceInfo::NetworkingService: return "NetworkingService";
    case QBluetoothDeviceInfo::RenderingService: return "RenderingService";
    case QBluetoothDeviceInfo::CapturingService: return "CapturingService";
    case QBluetoothDeviceInfo::ObjectTransferService: return "ObjectTransferService";
    case QBluetoothDeviceInfo::AudioService: return "AudioService";
    case QBluetoothDeviceInfo::TelephonyService: return "TelephonyService";
    case QBluetoothDeviceInfo::InformationService: return "InformationService";
    case QBluetoothDeviceInfo::AllServices: return "AllServices";
    default: return "Unknown";
    }
}
