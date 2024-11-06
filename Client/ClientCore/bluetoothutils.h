// BluetoothUtils.h
#ifndef BLUETOOTHUTILS_H
#define BLUETOOTHUTILS_H

#include <QString>
#include <QStringList>
#include <QBluetoothDeviceInfo>

class BluetoothUtils {
public:
    // CoreConfiguration
    static QString coreConfigurationToString(QBluetoothDeviceInfo::CoreConfigurations configs);

    // Field
    static QString fieldToString(QBluetoothDeviceInfo::Fields fields);

    // MajorDeviceClass
    static QString majorDeviceClassToString(QBluetoothDeviceInfo::MajorDeviceClass majorClass);

    // MinorAudioVideoClass
    static QString minorAudioVideoClassToString(QBluetoothDeviceInfo::MinorAudioVideoClass minorClass);

    // MinorComputerClass
    static QString minorComputerClassToString(QBluetoothDeviceInfo::MinorComputerClass minorClass);

    // MinorHealthClass
    static QString minorHealthClassToString(QBluetoothDeviceInfo::MinorHealthClass minorClass);

    // MinorImagingClass
    static QString minorImagingClassToString(QBluetoothDeviceInfo::MinorImagingClass minorClass);

    // MinorMiscellaneousClass
    static QString minorMiscellaneousClassToString(QBluetoothDeviceInfo::MinorMiscellaneousClass minorClass);

    // MinorNetworkClass
    static QString minorNetworkClassToString(QBluetoothDeviceInfo::MinorNetworkClass minorClass);

    // MinorPeripheralClass
    static QString minorPeripheralClassToString(QBluetoothDeviceInfo::MinorPeripheralClass minorClass);

    // MinorPhoneClass
    static QString minorPhoneClassToString(QBluetoothDeviceInfo::MinorPhoneClass minorClass);

    // MinorToyClass
    static QString minorToyClassToString(QBluetoothDeviceInfo::MinorToyClass minorClass);

    // MinorWearableClass
    static QString minorWearableClassToString(QBluetoothDeviceInfo::MinorWearableClass minorClass);

    // ServiceClass
    static QString serviceClassToString(QBluetoothDeviceInfo::ServiceClasses services);
};

#endif // BLUETOOTHUTILS_H
