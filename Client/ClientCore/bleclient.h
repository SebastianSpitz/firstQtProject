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

    // EventBus connected methods


    // DeviceDiscoveryAgent connected methods

    // EnergyController connected methods

    // EnergyService connected methods


    void setTargetDeviceName(const QString &name);
    void startDeviceDiscovery();
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
    bool sendData(const QByteArray &data);
    void dataReceived(const QLowEnergyCharacteristic &c, const QByteArray &value);
    void descriptorWritten(const QLowEnergyDescriptor &d, const QByteArray &value);

    QVariantMap statusRequest();
    EventBus *eventBus;
    Logger *logger;
    QString targetDeviceName;
    QBluetoothDeviceDiscoveryAgent *deviceDiscoveryAgent;
    QLowEnergyController *energyController;
    QLowEnergyService *energyService;
    QLowEnergyCharacteristic writeCharacteristic;
    QLowEnergyCharacteristic readCharacteristic;
    QLowEnergyDescriptor notificationDesc;
};

#endif // BLECLIENT_H
