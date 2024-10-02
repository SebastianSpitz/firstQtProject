#include "sbccore.h"

SBCCore::SBCCore(QObject *parent)
    : QObject(parent)
{
    bleServer = new BLEServer(this);
    connect(bleServer, &BLEServer::sigConnected, this, &SBCCore::bleConnected);
    connect(bleServer, &BLEServer::sigDisconnected, this, &SBCCore::bleDisconnected);
    connect(bleServer, &BLEServer::sigDataReceived, this, &SBCCore::bleDataReceived);
    connect(bleServer, &BLEServer::sigErrorOccurred, this, &SBCCore::bleErrorOccurred);

    sbc_io = new SBCIO(this);
    connect(sbc_io, &SBCIO::sigErrorOccurred, this, &SBCCore::sbc_io_ErrorOccurred);

}

    // BLEServer connections
void SBCCore::bleDataReceived(QVariant data)
{

}

void SBCCore::bleConnected(QString clientName)
{

}

void SBCCore::bleDisconnected(QString clientName)
{

}

void SBCCore::bleErrorOccurred(QString errorString)
{

}


    // SBC_IO connections
void SBCCore::sbc_io_ErrorOccurred(QString errorString)
{

}

    // Public methods
void SBCCore::startBLEServer(QString serverName)
{

}

void SBCCore::stopBLEServer()
{

}

void SBCCore::sendBLEData(QVariant data)
{

}






