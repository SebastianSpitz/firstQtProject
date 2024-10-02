#ifndef CLIENTCORE_H
#define CLIENTCORE_H

#include <QObject>
#include <QDebug>

#include "bleclient.h"

class ClientCore : public QObject
{
    Q_OBJECT

public:
    ClientCore(QObject *parent = nullptr);

    void connectToServer(QString serverName);
    void searchServer();
    void sendData(QVariant data);

private:
    BLEClient *bleClient;

    void bleDataReceived(QVariant data);
    void bleServerFound(QString serverName);
    void bleConnected(QString serverName);
    void bleDisconnected(QString serverName);
    void bleError(QString errorString);

signals:
    void sigServerFound(QString serverName);
    void sigConnected(QString serverName);
    void sigDisconnected(QString serverName);
    void sigDataReceived(QVariant data);
    void sigErrorOccurred(QString errorString);
};

#endif // CLIENTCORE_H
