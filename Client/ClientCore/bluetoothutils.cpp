// BluetoothUtils.cpp
#include "bluetoothutils.h"

// Convert QBluetoothDeviceInfo into QVariantMap object
QVariantMap BluetoothUtils::deviceInfoToVariantMap(const QBluetoothDeviceInfo &deviceInfo)
{
    QVariantMap map;

    // address()
    map["address"] = deviceInfo.address().toString();

    // coreConfigurations()
    map["coreConfigurations"] = coreConfigurationToString(deviceInfo.coreConfigurations());

    // deviceUuid()
    map["deviceUuid"] = deviceInfo.deviceUuid().toString();

    // isCached()
    map["isCached"] = deviceInfo.isCached();

    // isValid()
    map["isValid"] = deviceInfo.isValid();

    // majorDeviceClass()
    map["majorDeviceClass"] = majorDeviceClassToString(deviceInfo.majorDeviceClass());

    // minorDeviceClass()
    map["minorDeviceClass"] = minorDeviceClassToString(deviceInfo.majorDeviceClass(), deviceInfo.minorDeviceClass());

    // manufacturerData()
    QMultiHash<quint16, QByteArray> manufacturerData = deviceInfo.manufacturerData();
    QVariantList manufacturerDataList;
    for (auto it = manufacturerData.constBegin(); it != manufacturerData.constEnd(); ++it) {
        QVariantMap dataEntry;
        dataEntry["manufacturerId"] = static_cast<int>(it.key());
        dataEntry["data"] = QString::fromLatin1(it.value().toHex());
        manufacturerDataList.append(dataEntry);
    }
    map["manufacturerData"] = manufacturerDataList;

    // manufacturerIds()
    QList<quint16> manufacturerIds = deviceInfo.manufacturerIds();
    QVariantList manufacturerIdsList;
    for (quint16 id : manufacturerIds) {
        manufacturerIdsList.append(static_cast<int>(id));
    }
    map["manufacturerIds"] = manufacturerIdsList;

    // name()
    map["name"] = deviceInfo.name();

    // rssi()
    map["rssi"] = deviceInfo.rssi();

    // serviceClasses()
    map["serviceClasses"] = serviceClassToString(deviceInfo.serviceClasses());

    // serviceData()
    QMultiHash<QBluetoothUuid, QByteArray> serviceData = deviceInfo.serviceData();
    QVariantList serviceDataList;
    for (auto it = serviceData.constBegin(); it != serviceData.constEnd(); ++it) {
        QVariantMap dataEntry;
        dataEntry["serviceUuid"] = it.key().toString();
        dataEntry["data"] = QString::fromLatin1(it.value().toHex());
        serviceDataList.append(dataEntry);
    }
    map["serviceData"] = serviceDataList;

    // serviceIds()
    QList<QBluetoothUuid> serviceIds = deviceInfo.serviceIds();
    QVariantList serviceIdsList;
    for (const QBluetoothUuid &uuid : serviceIds) {
        serviceIdsList.append(uuid.toString());
    }
    map["serviceIds"] = serviceIdsList;

    // serviceUuids()
    QList<QBluetoothUuid> serviceUuids = deviceInfo.serviceUuids();
    QVariantList serviceUuidsList;
    for (const QBluetoothUuid &uuid : serviceUuids) {
        serviceUuidsList.append(uuid.toString());
    }
    map["serviceUuids"] = serviceUuidsList;

    return map;
}


// CoreConfiguration
QString BluetoothUtils::coreConfigurationToString(QBluetoothDeviceInfo::CoreConfigurations configs) {
    QStringList configList;

    if (configs & QBluetoothDeviceInfo::BaseRateCoreConfiguration)
        configList << "BaseRateCoreConfiguration";
    if (configs & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
        configList << "LowEnergyCoreConfiguration";
    if (configs & QBluetoothDeviceInfo::BaseRateAndLowEnergyCoreConfiguration)
        configList << "BaseRateAndLowEnergyCoreConfiguration";
    if (configList.isEmpty())
        configList << "UnknownCoreConfiguration";

    return configList.join(", ");
}

// Field
QString BluetoothUtils::fieldToString(QBluetoothDeviceInfo::Fields fields) {
    QStringList fieldList;

    if (fields & QBluetoothDeviceInfo::Field::RSSI)
        fieldList << "RSSI";
    if (fields & QBluetoothDeviceInfo::Field::ManufacturerData)
        fieldList << "ManufacturerData";
    if (fields & QBluetoothDeviceInfo::Field::ServiceData)
        fieldList << "ServiceData";
    if (fields == QBluetoothDeviceInfo::Field::None)
        fieldList << "None";
    if (fields == QBluetoothDeviceInfo::Field::All)
        fieldList << "All";

    return fieldList.join(", ");
}

// MajorDeviceClass
QString BluetoothUtils::majorDeviceClassToString(QBluetoothDeviceInfo::MajorDeviceClass majorClass) {
    switch (majorClass) {
    case QBluetoothDeviceInfo::MiscellaneousDevice:
        return "Miscellaneous Device";
    case QBluetoothDeviceInfo::ComputerDevice:
        return "Computer Device";
    case QBluetoothDeviceInfo::PhoneDevice:
        return "Phone Device";
    case QBluetoothDeviceInfo::NetworkDevice:
        return "Network Device";
    case QBluetoothDeviceInfo::AudioVideoDevice:
        return "AudioVideo Device";
    case QBluetoothDeviceInfo::PeripheralDevice:
        return "Peripheral Device";
    case QBluetoothDeviceInfo::ImagingDevice:
        return "Imaging Device";
    case QBluetoothDeviceInfo::WearableDevice:
        return "Wearable Device";
    case QBluetoothDeviceInfo::ToyDevice:
        return "Toy Device";
    case QBluetoothDeviceInfo::HealthDevice:
        return "Health Device";
    case QBluetoothDeviceInfo::UncategorizedDevice:
        return "Uncategorized Device";
    default:
        return "Unknown Major Device Class";
    }
}

// ServiceClass
QString BluetoothUtils::serviceClassToString(QBluetoothDeviceInfo::ServiceClasses services) {
    QStringList serviceList;

    if (services & QBluetoothDeviceInfo::PositioningService)
        serviceList << "PositioningService";
    if (services & QBluetoothDeviceInfo::NetworkingService)
        serviceList << "NetworkingService";
    if (services & QBluetoothDeviceInfo::RenderingService)
        serviceList << "RenderingService";
    if (services & QBluetoothDeviceInfo::CapturingService)
        serviceList << "CapturingService";
    if (services & QBluetoothDeviceInfo::ObjectTransferService)
        serviceList << "ObjectTransferService";
    if (services & QBluetoothDeviceInfo::AudioService)
        serviceList << "AudioService";
    if (services & QBluetoothDeviceInfo::TelephonyService)
        serviceList << "TelephonyService";
    if (services & QBluetoothDeviceInfo::InformationService)
        serviceList << "InformationService";
    if (services == QBluetoothDeviceInfo::NoService)
        serviceList << "NoService";
    if (services == QBluetoothDeviceInfo::AllServices)
        serviceList << "AllServices";

    return serviceList.join(", ");
}

static QString minorDeviceClassToString(QBluetoothDeviceInfo::MajorDeviceClass majorClass, quint8 minorClass)
{
    switch (majorClass) {
    case QBluetoothDeviceInfo::ComputerDevice:
        switch (static_cast<QBluetoothDeviceInfo::MinorComputerClass>(minorClass)) {
        case QBluetoothDeviceInfo::UncategorizedComputer:
            return "Uncategorized Computer";
        case QBluetoothDeviceInfo::DesktopComputer:
            return "Desktop Computer";
        case QBluetoothDeviceInfo::ServerComputer:
            return "Server Computer";
        case QBluetoothDeviceInfo::LaptopComputer:
            return "Laptop Computer";
        case QBluetoothDeviceInfo::HandheldClamShellComputer:
            return "Handheld Clamshell Computer";
        case QBluetoothDeviceInfo::HandheldComputer:
            return "Handheld Computer";
        case QBluetoothDeviceInfo::WearableComputer:
            return "Wearable Computer";
        default:
            return "Unknown Computer Device";
        }
    case QBluetoothDeviceInfo::PhoneDevice:
        switch (static_cast<QBluetoothDeviceInfo::MinorPhoneClass>(minorClass)) {
        case QBluetoothDeviceInfo::UncategorizedPhone:
            return "Uncategorized Phone";
        case QBluetoothDeviceInfo::CellularPhone:
            return "Cellular Phone";
        case QBluetoothDeviceInfo::CordlessPhone:
            return "Cordless Phone";
        case QBluetoothDeviceInfo::SmartPhone:
            return "Smartphone";
        case QBluetoothDeviceInfo::WiredModemOrVoiceGatewayPhone:
            return "Wired Modem or Voice Gateway";
        case QBluetoothDeviceInfo::CommonIsdnAccessPhone:
            return "Common ISDN Access";
        default:
            return "Unknown Phone Device";
        }
    case QBluetoothDeviceInfo::NetworkDevice:
        switch (static_cast<QBluetoothDeviceInfo::MinorNetworkClass>(minorClass)) {
        case QBluetoothDeviceInfo::NetworkFullService:
            return "Network Full Service";
        case QBluetoothDeviceInfo::NetworkLoadFactorOne:
            return "Network Load Factor 1";
        case QBluetoothDeviceInfo::NetworkLoadFactorTwo:
            return "Network Load Factor 2";
        case QBluetoothDeviceInfo::NetworkLoadFactorThree:
            return "Network Load Factor 3";
        case QBluetoothDeviceInfo::NetworkLoadFactorFour:
            return "Network Load Factor 4";
        case QBluetoothDeviceInfo::NetworkLoadFactorFive:
            return "Network Load Factor 5";
        case QBluetoothDeviceInfo::NetworkLoadFactorSix:
            return "Network Load Factor 6";
        case QBluetoothDeviceInfo::NetworkNoService:
            return "Network No Service";
        default:
            return "Unknown Network Device";
        }
    case QBluetoothDeviceInfo::AudioVideoDevice:
        switch (static_cast<QBluetoothDeviceInfo::MinorAudioVideoClass>(minorClass)) {
        case QBluetoothDeviceInfo::UncategorizedAudioVideoDevice:
            return "Uncategorized Audio/Video Device";
        case QBluetoothDeviceInfo::WearableHeadsetDevice:
            return "Wearable Headset Device";
        case QBluetoothDeviceInfo::HandsFreeDevice:
            return "Hands-Free Device";
        case QBluetoothDeviceInfo::Microphone:
            return "Microphone";
        case QBluetoothDeviceInfo::Loudspeaker:
            return "Loudspeaker";
        case QBluetoothDeviceInfo::Headphones:
            return "Headphones";
        case QBluetoothDeviceInfo::PortableAudioDevice:
            return "Portable Audio Device";
        case QBluetoothDeviceInfo::CarAudio:
            return "Car Audio";
        case QBluetoothDeviceInfo::SetTopBox:
            return "Set-Top Box";
        case QBluetoothDeviceInfo::HiFiAudioDevice:
            return "Hi-Fi Audio Device";
        case QBluetoothDeviceInfo::Vcr:
            return "VCR";
        case QBluetoothDeviceInfo::VideoCamera:
            return "Video Camera";
        case QBluetoothDeviceInfo::Camcorder:
            return "Camcorder";
        case QBluetoothDeviceInfo::VideoMonitor:
            return "Video Monitor";
        case QBluetoothDeviceInfo::VideoDisplayAndLoudspeaker:
            return "Video Display and Loudspeaker";
        case QBluetoothDeviceInfo::VideoConferencing:
            return "Video Conferencing";
        case QBluetoothDeviceInfo::GamingDevice:
            return "Gaming Device";
        default:
            return "Unknown Audio/Video Device";
        }
    case QBluetoothDeviceInfo::PeripheralDevice:
        switch (static_cast<QBluetoothDeviceInfo::MinorPeripheralClass>(minorClass)) {
        case QBluetoothDeviceInfo::UncategorizedPeripheral:
            return "Uncategorized Peripheral";
        case QBluetoothDeviceInfo::KeyboardPeripheral:
            return "Keyboard";
        case QBluetoothDeviceInfo::PointingDevicePeripheral:
            return "Pointing Device";
        case QBluetoothDeviceInfo::KeyboardWithPointingDevicePeripheral:
            return "Keyboard with Pointing Device";
        case QBluetoothDeviceInfo::JoystickPeripheral:
            return "Joystick";
        case QBluetoothDeviceInfo::GamepadPeripheral:
            return "Gamepad";
        case QBluetoothDeviceInfo::RemoteControlPeripheral:
            return "Remote Control";
        case QBluetoothDeviceInfo::SensingDevicePeripheral:
            return "Sensing Device";
        case QBluetoothDeviceInfo::DigitizerTabletPeripheral:
            return "Digitizer Tablet";
        case QBluetoothDeviceInfo::CardReaderPeripheral:
            return "Card Reader";
        default:
            return "Unknown Peripheral Device";
        }
    case QBluetoothDeviceInfo::ImagingDevice:
        switch (static_cast<QBluetoothDeviceInfo::MinorImagingClass>(minorClass)) {
        case QBluetoothDeviceInfo::UncategorizedImagingDevice:
            return "Uncategorized Imaging Device";
        case QBluetoothDeviceInfo::ImageDisplay:
            return "Image Display";
        case QBluetoothDeviceInfo::ImageCamera:
            return "Image Camera";
        case QBluetoothDeviceInfo::ImageScanner:
            return "Image Scanner";
        case QBluetoothDeviceInfo::ImagePrinter:
            return "Image Printer";
        default:
            return "Unknown Imaging Device";
        }
    case QBluetoothDeviceInfo::WearableDevice:
        switch (static_cast<QBluetoothDeviceInfo::MinorWearableClass>(minorClass)) {
        case QBluetoothDeviceInfo::UncategorizedWearableDevice:
            return "Uncategorized Wearable Device";
        case QBluetoothDeviceInfo::WearableWristWatch:
            return "Wearable Wrist Watch";
        case QBluetoothDeviceInfo::WearablePager:
            return "Wearable Pager";
        case QBluetoothDeviceInfo::WearableJacket:
            return "Wearable Jacket";
        case QBluetoothDeviceInfo::WearableHelmet:
            return "Wearable Helmet";
        case QBluetoothDeviceInfo::WearableGlasses:
            return "Wearable Glasses";
        default:
            return "Unknown Wearable Device";
        }
    case QBluetoothDeviceInfo::ToyDevice:
        switch (static_cast<QBluetoothDeviceInfo::MinorToyClass>(minorClass)) {
        case QBluetoothDeviceInfo::UncategorizedToy:
            return "Uncategorized Toy";
        case QBluetoothDeviceInfo::ToyRobot:
            return "Toy Robot";
        case QBluetoothDeviceInfo::ToyVehicle:
            return "Toy Vehicle";
        case QBluetoothDeviceInfo::ToyDoll:
            return "Toy Doll or Action Figure";
        case QBluetoothDeviceInfo::ToyController:
            return "Toy Controller";
        case QBluetoothDeviceInfo::ToyGame:
            return "Toy Game";
        default:
            return "Unknown Toy Device";
        }
    case QBluetoothDeviceInfo::HealthDevice:
        switch (static_cast<QBluetoothDeviceInfo::MinorHealthClass>(minorClass)) {
        case QBluetoothDeviceInfo::UncategorizedHealthDevice:
            return "Uncategorized Health Device";
        case QBluetoothDeviceInfo::HealthBloodPressureMonitor:
            return "Blood Pressure Monitor";
        case QBluetoothDeviceInfo::HealthThermometer:
            return "Thermometer";
        case QBluetoothDeviceInfo::HealthWeightScale:
            return "Weight Scale";
        case QBluetoothDeviceInfo::HealthGlucoseMeter:
            return "Glucose Meter";
        case QBluetoothDeviceInfo::HealthPulseOximeter:
            return "Pulse Oximeter";
        case QBluetoothDeviceInfo::HealthDataDisplay:
            return "Data Display";
        case QBluetoothDeviceInfo::HealthStepCounter:
            return "Step Counter";
        default:
            return "Unknown Health Device";
        }
    case QBluetoothDeviceInfo::MiscellaneousDevice:
        switch (static_cast<QBluetoothDeviceInfo::MinorMiscellaneousClass>(minorClass)) {
        case QBluetoothDeviceInfo::UncategorizedMiscellaneous:
            return "Uncategorized Miscellaneous Device";
        default:
            return "Unknown Miscellaneous Device";
        }
    case QBluetoothDeviceInfo::UncategorizedDevice:
        return "Uncategorized Device";
    default:
        return "Unknown Device Class";
    }
}

