#ifndef CLIENTGUI_H
#define CLIENTGUI_H

#include <QObject>
#include <QSettings>

#include "eventbus.h"
#include "clientcore.h"

class ClientGui : public QObject
{
    Q_OBJECT

public:
    explicit ClientGui(QObject *parent = nullptr);

    EventBus* getEventBus();

private:
    ClientCore *clientCore;

};

#endif // CLIENTGUI_H
