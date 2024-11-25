#include "clientgui.h"

// Constructor
ClientGui::ClientGui(QObject *parent)
    : QObject{parent}
{
    clientCore = new ClientCore(this);
}


    // Public methods

EventBus *ClientGui::getEventBus()
{
    return clientCore->getEventBus();
}
