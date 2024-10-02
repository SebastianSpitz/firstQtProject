#ifndef BLECLIENT_H
#define BLECLIENT_H

#include <QObject>
#include <QBluetoothLocalDevice>
#include <QCoreApplication>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QLowEnergyCharacteristic>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyDescriptor>
#include <QVariant>
#include <QPermission>

class BLEClient : public QObject
{
    Q_OBJECT

public:
    explicit BLEClient(QObject *parent = nullptr);
    void searchServer();
    void connectToServer(QString serverName);
    void sendData(QVariant &value);

private:
    // Agent connections
    void agentDeviceDiscovered(const QBluetoothDeviceInfo &info);
    void agentError(QBluetoothDeviceDiscoveryAgent::Error error);
    void agentFinished();
    void agentCanceled();

    // Controller connections
    void controllerDiscovered(const QBluetoothUuid &newService);
    void controllerFinished();
    void controllerError(QLowEnergyController::Error newError);
    void controllerConnected();
    void controllerDisconnected();

    // Service connections
    void serviceStateChanged(QLowEnergyService::ServiceState newState);
    void serviceCharChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void serviceDescWritten(const QLowEnergyDescriptor &descriptor, const QByteArray &newValue);

    QString serverName;
    QBluetoothLocalDevice localDevice;
    QBluetoothDeviceDiscoveryAgent *agent;
    QLowEnergyController *controller;
    QLowEnergyService *service;
    QLowEnergyCharacteristic characteristic;

    QBluetoothUuid serviceUuid = QBluetoothUuid(QStringLiteral("12345678-1234-5678-1234-56789abcdef0"));
    QBluetoothUuid characteristicUuid = QBluetoothUuid(QStringLiteral("abcdef01-1234-5678-1234-56789abcdef0"));

signals:
    void sigServerFound(QString server);
    void sigDataReceived(QVariant &value);
    void sigConnected(QString serverName);
    void sigDisconnected(QString serverName);
    void sigErrorOccurred(QString errorString);
};

#endif // BLECLIENT_H
