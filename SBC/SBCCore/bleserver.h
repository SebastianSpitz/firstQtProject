#ifndef BLESERVER_H
#define BLESERVER_H

#include <QObject>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <QtBluetooth/QBluetoothUuid>
#include <QtBluetooth/QLowEnergyController>
#include <QtBluetooth/QLowEnergyService>
#include <QtBluetooth/QLowEnergyServiceData>
#include <QtBluetooth/QLowEnergyCharacteristicData>
#include <QtBluetooth/QLowEnergyCharacteristic>
#include <QtBluetooth/QLowEnergyDescriptor>
#include <QtBluetooth/QLowEnergyAdvertisingParameters>
#include <QtBluetooth/QLowEnergyDescriptorData>
#include <QPermission>
#include <QCoreApplication>
#include <QVariant>

class BLEServer : public QObject
{
    Q_OBJECT

public:
    explicit BLEServer(QObject *parent = nullptr);
    ~BLEServer();

    void startServer(QString serverName);
    void stopServer();
    void sendData(const QVariant &data);

private:
    // Controller connections
    void controllerConnected();
    void controllerDisconnected();
    void controllerServiceDiscovered(const QBluetoothUuid &newService);
    void controllerStateChanged(QLowEnergyController::ControllerState state);

    // Service connections
    void serviceCharWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &value);
    void serviceCharRead(const QLowEnergyCharacteristic &characteristic, const QByteArray &value);
    void serviceCharChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);


    QBluetoothLocalDevice localDevice;
    QLowEnergyController *controller;
    QLowEnergyService *service;
    QLowEnergyServiceData serviceData;
    QLowEnergyCharacteristic characteristic;
    QLowEnergyCharacteristicData charData;
    QLowEnergyAdvertisingData advertisingData;
    QString serverName;

    // Custom service and characteristic UUIDs
    const QBluetoothUuid serviceUuid = QBluetoothUuid("{12345678-1234-5678-1234-56789abcdef0}");
    const QBluetoothUuid charUuid = QBluetoothUuid("{12345678-1234-5678-1234-56789abcdef1}");
    const QBluetoothUuid rxUuid = QBluetoothUuid("{12345678-1234-5678-1234-56789abcdef2}");

signals:
    void sigDataReceived(const QVariant &data);
    void sigConnected(QString clientName);
    void sigDisconnected(QString clientName);
    void sigErrorOccurred(QString errorString);
};

#endif // BLESERVER_H
