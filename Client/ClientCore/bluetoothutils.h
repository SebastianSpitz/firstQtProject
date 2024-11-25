// BluetoothUtils.h
#ifndef BLUETOOTHUTILS_H
#define BLUETOOTHUTILS_H

#include <QString>
#include <QStringList>
#include <QBluetoothDeviceInfo>
#include <QVariantList>
#include <QMultiHash>
#include <QList>
#include <QByteArray>
#include <QBluetoothAddress>
#include <QBluetoothUuid>

class BluetoothUtils {
public:

    // Convert QBluetoothDeviceInfo into a QVariantMap object
    static QVariantMap deviceInfoToVariantMap(const QBluetoothDeviceInfo &deviceInfo);

    // CoreConfiguration
    static QString coreConfigurationToString(QBluetoothDeviceInfo::CoreConfigurations configs);

    // Field
    static QString fieldToString(QBluetoothDeviceInfo::Fields fields);

    // MajorDeviceClass
    static QString majorDeviceClassToString(QBluetoothDeviceInfo::MajorDeviceClass majorClass);

    // MinorDeviceClass
    static QString minorDeviceClassToString(QBluetoothDeviceInfo::MajorDeviceClass majorClass, quint8 minorClass);

    // ServiceClass
    static QString serviceClassToString(QBluetoothDeviceInfo::ServiceClasses services);
};

#endif // BLUETOOTHUTILS_H
