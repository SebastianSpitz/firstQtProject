#include "qmlinterface.h"

QmlInterface::QmlInterface(QObject *parent)
    : QObject{parent}
{
    qDebug() << "QmlInterface constructor called! Singleton created.";
}

QmlInterface *QmlInterface::getInstance()
{
    static QmlInterface instance;
    return &instance;
}

void QmlInterface::startBleServer()
{
    qDebug() << "startBleServer method call!";
    emit sigSignal();
}
