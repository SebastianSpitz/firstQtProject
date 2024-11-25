#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <QObject>

class EventBus : public QObject
{
    Q_OBJECT
public:
    explicit EventBus(QObject *parent = nullptr);

signals:
    // BLEClient
    void bleClientConnected(QVariantMap);
    void bleClientDisconnected(QVariantMap);
    void bleClientError(QVariantMap);
    void bleClientDeviceFound(QVariantMap);
    void bleClientDiscoveryFinished(QVariantList);
    void bleClientDataReceived(QVariantMap);
    bool bleClientSendData(QVariantMap);
    bool bleClientSearchServer(QVariantMap);
    bool bleClientDisconnect();

    // QML main
    void mainListViewItemClicked(QVariantMap);
    void mainConnectionButtonClicked();

    // QML bluetooth
    void blConnectionButtonClicked();
    void blListViewItemClicked(QVariantMap);
    void blSearchButtonClicked();

    // QML settings
    QVariantMap statusRequest();
};

#endif // EVENTBUS_H
