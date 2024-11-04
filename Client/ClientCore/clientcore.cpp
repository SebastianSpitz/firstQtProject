#include "clientcore.h"

ClientCore::ClientCore(QObject *parent)
    : QObject(parent)
{
    eventBus = new EventBus();
    logger = Logger::getInstance();
    bleClient = new BLEClient(this, eventBus);
}

EventBus *ClientCore::getEventBus()
{
    return eventBus;
}
