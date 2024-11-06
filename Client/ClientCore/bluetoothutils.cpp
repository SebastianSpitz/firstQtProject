// BluetoothUtils.cpp
#include "bluetoothutils.h"

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
        return "MiscellaneousDevice";
    case QBluetoothDeviceInfo::ComputerDevice:
        return "ComputerDevice";
    case QBluetoothDeviceInfo::PhoneDevice:
        return "PhoneDevice";
    case QBluetoothDeviceInfo::NetworkDevice:
        return "NetworkDevice";
    case QBluetoothDeviceInfo::AudioVideoDevice:
        return "AudioVideoDevice";
    case QBluetoothDeviceInfo::PeripheralDevice:
        return "PeripheralDevice";
    case QBluetoothDeviceInfo::ImagingDevice:
        return "ImagingDevice";
    case QBluetoothDeviceInfo::WearableDevice:
        return "WearableDevice";
    case QBluetoothDeviceInfo::ToyDevice:
        return "ToyDevice";
    case QBluetoothDeviceInfo::HealthDevice:
        return "HealthDevice";
    case QBluetoothDeviceInfo::UncategorizedDevice:
        return "UncategorizedDevice";
    default:
        return "UnknownMajorDeviceClass";
    }
}

// MinorAudioVideoClass
QString BluetoothUtils::minorAudioVideoClassToString(QBluetoothDeviceInfo::MinorAudioVideoClass minorClass) {
    switch (minorClass) {
    case QBluetoothDeviceInfo::UncategorizedAudioVideoDevice:
        return "UncategorizedAudioVideoDevice";
    case QBluetoothDeviceInfo::WearableHeadsetDevice:
        return "WearableHeadsetDevice";
    case QBluetoothDeviceInfo::HandsFreeDevice:
        return "HandsFreeDevice";
    case QBluetoothDeviceInfo::Microphone:
        return "Microphone";
    case QBluetoothDeviceInfo::Loudspeaker:
        return "Loudspeaker";
    case QBluetoothDeviceInfo::Headphones:
        return "Headphones";
    case QBluetoothDeviceInfo::PortableAudioDevice:
        return "PortableAudioDevice";
    case QBluetoothDeviceInfo::CarAudio:
        return "CarAudio";
    case QBluetoothDeviceInfo::SetTopBox:
        return "SetTopBox";
    case QBluetoothDeviceInfo::HiFiAudioDevice:
        return "HiFiAudioDevice";
    case QBluetoothDeviceInfo::Vcr:
        return "Vcr";
    case QBluetoothDeviceInfo::VideoCamera:
        return "VideoCamera";
    case QBluetoothDeviceInfo::Camcorder:
        return "Camcorder";
    case QBluetoothDeviceInfo::VideoMonitor:
        return "VideoMonitor";
    case QBluetoothDeviceInfo::VideoDisplayAndLoudspeaker:
        return "VideoDisplayAndLoudspeaker";
    case QBluetoothDeviceInfo::VideoConferencing:
        return "VideoConferencing";
    case QBluetoothDeviceInfo::GamingDevice:
        return "GamingDevice";
    default:
        return "UnknownMinorAudioVideoClass";
    }
}

// MinorComputerClass
QString BluetoothUtils::minorComputerClassToString(QBluetoothDeviceInfo::MinorComputerClass minorClass) {
    switch (minorClass) {
    case QBluetoothDeviceInfo::UncategorizedComputer:
        return "UncategorizedComputer";
    case QBluetoothDeviceInfo::DesktopComputer:
        return "DesktopComputer";
    case QBluetoothDeviceInfo::ServerComputer:
        return "ServerComputer";
    case QBluetoothDeviceInfo::LaptopComputer:
        return "LaptopComputer";
    case QBluetoothDeviceInfo::HandheldClamShellComputer:
        return "HandheldClamShellComputer";
    case QBluetoothDeviceInfo::HandheldComputer:
        return "HandheldComputer";
    case QBluetoothDeviceInfo::WearableComputer:
        return "WearableComputer";
    default:
        return "UnknownMinorComputerClass";
    }
}

// MinorHealthClass
QString BluetoothUtils::minorHealthClassToString(QBluetoothDeviceInfo::MinorHealthClass minorClass) {
    switch (minorClass) {
    case QBluetoothDeviceInfo::UncategorizedHealthDevice:
        return "UncategorizedHealthDevice";
    case QBluetoothDeviceInfo::HealthBloodPressureMonitor:
        return "HealthBloodPressureMonitor";
    case QBluetoothDeviceInfo::HealthThermometer:
        return "HealthThermometer";
    case QBluetoothDeviceInfo::HealthWeightScale:
        return "HealthWeightScale";
    case QBluetoothDeviceInfo::HealthGlucoseMeter:
        return "HealthGlucoseMeter";
    case QBluetoothDeviceInfo::HealthPulseOximeter:
        return "HealthPulseOximeter";
    case QBluetoothDeviceInfo::HealthDataDisplay:
        return "HealthDataDisplay";
    case QBluetoothDeviceInfo::HealthStepCounter:
        return "HealthStepCounter";
    default:
        return "UnknownMinorHealthClass";
    }
}

// MinorImagingClass
QString BluetoothUtils::minorImagingClassToString(QBluetoothDeviceInfo::MinorImagingClass minorClass) {
    switch (minorClass) {
    case QBluetoothDeviceInfo::UncategorizedImagingDevice:
        return "UncategorizedImagingDevice";
    case QBluetoothDeviceInfo::ImageDisplay:
        return "ImageDisplay";
    case QBluetoothDeviceInfo::ImageCamera:
        return "ImageCamera";
    case QBluetoothDeviceInfo::ImageScanner:
        return "ImageScanner";
    case QBluetoothDeviceInfo::ImagePrinter:
        return "ImagePrinter";
    default:
        return "UnknownMinorImagingClass";
    }
}

// MinorMiscellaneousClass
QString BluetoothUtils::minorMiscellaneousClassToString(QBluetoothDeviceInfo::MinorMiscellaneousClass minorClass) {
    switch (minorClass) {
    case QBluetoothDeviceInfo::UncategorizedMiscellaneous:
        return "UncategorizedMiscellaneous";
    default:
        return "UnknownMinorMiscellaneousClass";
    }
}

// MinorNetworkClass
QString BluetoothUtils::minorNetworkClassToString(QBluetoothDeviceInfo::MinorNetworkClass minorClass) {
    switch (minorClass) {
    case QBluetoothDeviceInfo::NetworkFullService:
        return "NetworkFullService";
    case QBluetoothDeviceInfo::NetworkLoadFactorOne:
        return "NetworkLoadFactorOne";
    case QBluetoothDeviceInfo::NetworkLoadFactorTwo:
        return "NetworkLoadFactorTwo";
    case QBluetoothDeviceInfo::NetworkLoadFactorThree:
        return "NetworkLoadFactorThree";
    case QBluetoothDeviceInfo::NetworkLoadFactorFour:
        return "NetworkLoadFactorFour";
    case QBluetoothDeviceInfo::NetworkLoadFactorFive:
        return "NetworkLoadFactorFive";
    case QBluetoothDeviceInfo::NetworkLoadFactorSix:
        return "NetworkLoadFactorSix";
    case QBluetoothDeviceInfo::NetworkNoService:
        return "NetworkNoService";
    default:
        return "UnknownMinorNetworkClass";
    }
}

// MinorPeripheralClass
QString BluetoothUtils::minorPeripheralClassToString(QBluetoothDeviceInfo::MinorPeripheralClass minorClass) {
    QStringList peripheralList;

    if (minorClass & QBluetoothDeviceInfo::KeyboardPeripheral)
        peripheralList << "KeyboardPeripheral";
    if (minorClass & QBluetoothDeviceInfo::PointingDevicePeripheral)
        peripheralList << "PointingDevicePeripheral";
    if (minorClass & QBluetoothDeviceInfo::KeyboardWithPointingDevicePeripheral)
        peripheralList << "KeyboardWithPointingDevicePeripheral";
    if (minorClass & QBluetoothDeviceInfo::JoystickPeripheral)
        peripheralList << "JoystickPeripheral";
    if (minorClass & QBluetoothDeviceInfo::GamepadPeripheral)
        peripheralList << "GamepadPeripheral";
    if (minorClass & QBluetoothDeviceInfo::RemoteControlPeripheral)
        peripheralList << "RemoteControlPeripheral";
    if (minorClass & QBluetoothDeviceInfo::SensingDevicePeripheral)
        peripheralList << "SensingDevicePeripheral";
    if (minorClass & QBluetoothDeviceInfo::DigitizerTabletPeripheral)
        peripheralList << "DigitizerTabletPeripheral";
    if (minorClass & QBluetoothDeviceInfo::CardReaderPeripheral)
        peripheralList << "CardReaderPeripheral";
    if (peripheralList.isEmpty())
        peripheralList << "UncategorizedPeripheral";

    return peripheralList.join(", ");
}

// MinorPhoneClass
QString BluetoothUtils::minorPhoneClassToString(QBluetoothDeviceInfo::MinorPhoneClass minorClass) {
    switch (minorClass) {
    case QBluetoothDeviceInfo::UncategorizedPhone:
        return "UncategorizedPhone";
    case QBluetoothDeviceInfo::CellularPhone:
        return "CellularPhone";
    case QBluetoothDeviceInfo::CordlessPhone:
        return "CordlessPhone";
    case QBluetoothDeviceInfo::SmartPhone:
        return "SmartPhone";
    case QBluetoothDeviceInfo::WiredModemOrVoiceGatewayPhone:
        return "WiredModemOrVoiceGatewayPhone";
    case QBluetoothDeviceInfo::CommonIsdnAccessPhone:
        return "CommonIsdnAccessPhone";
    default:
        return "UnknownMinorPhoneClass";
    }
}

// MinorToyClass
QString BluetoothUtils::minorToyClassToString(QBluetoothDeviceInfo::MinorToyClass minorClass) {
    switch (minorClass) {
    case QBluetoothDeviceInfo::UncategorizedToy:
        return "UncategorizedToy";
    case QBluetoothDeviceInfo::ToyRobot:
        return "ToyRobot";
    case QBluetoothDeviceInfo::ToyVehicle:
        return "ToyVehicle";
    case QBluetoothDeviceInfo::ToyDoll:
        return "ToyDoll";
    case QBluetoothDeviceInfo::ToyController:
        return "ToyController";
    case QBluetoothDeviceInfo::ToyGame:
        return "ToyGame";
    default:
        return "UnknownMinorToyClass";
    }
}

// MinorWearableClass
QString BluetoothUtils::minorWearableClassToString(QBluetoothDeviceInfo::MinorWearableClass minorClass) {
    switch (minorClass) {
    case QBluetoothDeviceInfo::UncategorizedWearableDevice:
        return "UncategorizedWearableDevice";
    case QBluetoothDeviceInfo::WearableWristWatch:
        return "WearableWristWatch";
    case QBluetoothDeviceInfo::WearablePager:
        return "WearablePager";
    case QBluetoothDeviceInfo::WearableJacket:
        return "WearableJacket";
    case QBluetoothDeviceInfo::WearableHelmet:
        return "WearableHelmet";
    case QBluetoothDeviceInfo::WearableGlasses:
        return "WearableGlasses";
    default:
        return "UnknownMinorWearableClass";
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
