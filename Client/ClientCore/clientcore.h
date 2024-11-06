#ifndef CLIENTCORE_H
#define CLIENTCORE_H

#include <QObject>
#include <QDebug>

#include "bleclient.h"
#include "eventbus.h"
#include "logger.h"
#include "bleclient.h"

class ClientCore : public QObject
{
    Q_OBJECT

public:
    ClientCore(QObject *parent = nullptr);

    EventBus *getEventBus();

private:
    EventBus *eventBus;
    Logger *logger;
    BleClient *bleClient;

};

#endif // CLIENTCORE_H
