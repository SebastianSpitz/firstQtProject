#include "bleserver.h"

BLEServer::BLEServer(QObject *parent) :
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

    // Creating advertising data for advertising the server
    advertisingData.setDiscoverability(QLowEnergyAdvertisingData::DiscoverabilityGeneral);
    advertisingData.setIncludePowerLevel(true);
    advertisingData.setLocalName(serverName);
    advertisingData.setServices(QList<QBluetoothUuid>() << serviceUuid);

    // Creating the controller for server mode
    controller = QLowEnergyController::createPeripheral();
    connect(controller, &QLowEnergyController::connected, this, &BLEServer::controllerConnected);
    connect(controller, &QLowEnergyController::disconnected, this, &BLEServer::controllerDisconnected);
    connect(controller, &QLowEnergyController::serviceDiscovered, this, &BLEServer::controllerServiceDiscovered);
    connect(controller, &QLowEnergyController::stateChanged, this, &BLEServer::controllerStateChanged);

    // Creating characteristic data
    charData.setUuid(charUuid);
    charData.setValue(QByteArray(2, 0));
    charData.setProperties(QLowEnergyCharacteristic::Notify);
    QLowEnergyDescriptorData clientConfig(QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration, QByteArray(2, 0));
    charData.addDescriptor(clientConfig);

    // serviceData = new QLowEnergyServiceData();
    serviceData.setType(QLowEnergyServiceData::ServiceTypePrimary);
    serviceData.setUuid(serviceUuid);
    serviceData.addCharacteristic(charData);

    service = controller->addService(serviceData);
    connect(service, &QLowEnergyService::characteristicChanged, this, &BLEServer::serviceCharChanged);
    connect(service, &QLowEnergyService::characteristicRead, this, &BLEServer::serviceCharRead);
    connect(service, &QLowEnergyService::characteristicWritten, this, &BLEServer::serviceCharWritten);

    // Start the BLE server
}

BLEServer::~BLEServer()
{
    delete controller;
}


    // Controller connections
void BLEServer::controllerConnected()
{

}

void BLEServer::controllerDisconnected()
{

}

void BLEServer::controllerServiceDiscovered(const QBluetoothUuid &newService)
{

}

void BLEServer::controllerStateChanged(QLowEnergyController::ControllerState state)
{

}


    // Service connections
void BLEServer::serviceCharRead(const QLowEnergyCharacteristic &characteristic, const QByteArray &value)
{

}

void BLEServer::serviceCharChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue)
{

}


void BLEServer::serviceCharWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &value)
{
    if (characteristic.uuid() == characteristic.uuid()) {
        QVariant data = QVariant::fromValue(value);
        emit sigDataReceived(data);
    }
}


    // Public methods
void BLEServer::startServer(QString serverName)
{
    this->serverName = serverName;
    controller->startAdvertising(QLowEnergyAdvertisingParameters(), advertisingData, advertisingData);
}

void BLEServer::stopServer()
{
    controller->stopAdvertising();
}

void BLEServer::sendData(const QVariant &data)
{
    QByteArray byteArray = data.toByteArray();
    service->writeCharacteristic(characteristic, byteArray);
}




