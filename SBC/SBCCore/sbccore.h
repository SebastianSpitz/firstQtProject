#ifndef SBCCORE_H
#define SBCCORE_H

#include <QObject>
#include <QDebug>
#include <QVariant>

#include "bleserver.h"
#include "sbcio.h"

class SBCCore : public QObject
{
    Q_OBJECT

public:
    SBCCore(QObject *parent = nullptr);

    void startBLEServer(QString serverName);
    void stopBLEServer();
    void sendBLEData(QVariant data);

private:
    BLEServer *bleServer;
    SBCIO *sbc_io;

    void bleDataReceived(QVariant data);
    void bleConnected(QString clientName);
    void bleDisconnected(QString clientName);
    void bleErrorOccurred(QString errorString);
    void sbc_io_ErrorOccurred(QString errorString);

signals:
    void sigConnected(QString clientName);
    void sigDisconnected(QString clientName);
    void sigDataReceived(QVariant data);
    void sigErrorOccurred(QString errorString);

};

#endif // SBCCORE_H
