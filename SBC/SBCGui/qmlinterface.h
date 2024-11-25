#ifndef QMLINTERFACE_H
#define QMLINTERFACE_H

#include <QObject>
#include <QQmlEngine>

class QmlInterface : public QObject
{
    Q_OBJECT
    //QML_SINGLETON
    //QML_ELEMENT

public:
    static QmlInterface *getInstance();

    Q_INVOKABLE void startBleServer();

private:
    QmlInterface(QObject *parent = nullptr);

signals:
    void sigSignal();
};

#endif // QMLINTERFACE_H
