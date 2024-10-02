#include "clientcore.h"

ClientCore::ClientCore(QObject *parent)
    : QObject(parent)
{
    // Create BLEClient
    bleClient = new BLEClient(this);
    connect(bleClient, &BLEClient::sigDataReceived, this, &ClientCore::bleDataReceived);
    connect(bleClient, &BLEClient::sigServerFound, this, &ClientCore::bleServerFound);
    connect(bleClient, &BLEClient::sigConnected, this, &ClientCore::bleConnected);
    connect(bleClient, &BLEClient::sigDisconnected, this, &ClientCore::bleDisconnected);

}

void ClientCore::connectToServer(QString serverName)
{
    bleClient->connectToServer(serverName);
}

void ClientCore::searchServer()
{
    bleClient->searchServer();
}

    // Core connections
void ClientCore::bleDataReceived(QVariant data)
{
    emit sigDataReceived(data);
}

void ClientCore::bleServerFound(QString serverName)
{
    emit sigServerFound(serverName);
}

void ClientCore::bleConnected(QString serverName)
{
    emit sigConnected(serverName);
}

void ClientCore::bleDisconnected(QString serverName)
{
    emit sigDisconnected(serverName);
}




