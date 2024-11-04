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
    void bleDataReceived(QVariantMap);
    bool bleSendData(QVariantMap);

    // QML main
    void mainListViewItemClicked(QVariantMap);
    void mainConnectionButtonClicked();

    // QML bluetooth
    void blConnectionButtonClicked();
    void blListViewItemClicked(QVariantMap);
    void blSearchButtonClicked();

    //
    QVariantMap statusRequest();
};

#endif // EVENTBUS_H
