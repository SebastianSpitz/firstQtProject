#ifndef BLECLIENT_H
#define BLECLIENT_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QBluetoothDeviceInfo>
#include <QBluetoothUuid>
#include <QList>
#include <QTimer>

#include "eventbus.h"
#include "logger.h"
#include "bluetoothutils.h"

class BleClient : public QObject
{
    Q_OBJECT

public:
    explicit BleClient(QObject *parent = nullptr, EventBus *eventBus = nullptr);
    ~BleClient();

private:

    // Sets the target device name to search for
    void setTargetDeviceName(const QString &name);

    // Starts scanning for BLE devices
    void startDeviceDiscovery();

    // Sends data to the BLE server
    void sendData(const QByteArray &data);

    // Disconnects from the current BLE device
    void disconnectFromDevice();

    void deviceDiscoveryDeviceDiscovered(const QBluetoothDeviceInfo &deviceInfo);
    void deviceDiscoveryFinished();
    void deviceDiscoveryError();
    void controllerConnected();
    void controllerDisconnected();
    void controllerErrorOccurred(QLowEnergyController::Error error);
    void serviceDiscoveredHandler(const QBluetoothUuid &serviceUuid);
    void serviceScanDone();
    void serviceStateChanged(QLowEnergyService::ServiceState s);
    void characteristicChanged(const QLowEnergyCharacteristic &c, const QByteArray &value);
    void descriptorWritten(const QLowEnergyDescriptor &d, const QByteArray &value);

    QVariantMap statusRequest();
    EventBus *eventBus;
    Logger *logger;
    QString m_targetDeviceName;
    QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent;
    QLowEnergyController *m_control;
    QLowEnergyService *m_service;
    QLowEnergyCharacteristic m_writeCharacteristic;
    QLowEnergyCharacteristic m_readCharacteristic;
    QLowEnergyDescriptor m_notificationDesc;
};

#endif // BLECLIENT_H
