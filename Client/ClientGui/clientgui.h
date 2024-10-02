#ifndef CLIENTGUI_H
#define CLIENTGUI_H

#include <QObject>
#include <QSettings>

#include "qmlinterface.h"
#include "clientcore.h"

class ClientGui : public QObject
{
    Q_OBJECT

public:
    explicit ClientGui(QObject *parent = nullptr, QmlInterface *qmlInterface = nullptr);

    void connectToServer(QString serverName);
    void searchServer();
    void sendData(QVariant data);

private:
    ClientCore *clientCore;
    QmlInterface *qmlInterface;

    // core methods
    void coreServerFound(QString serverName);
    void coreConnected(QString serverName);
    void coreDisconnected(QString serverName);
    void coreDataReceived(QVariant data);
    void coreErrorOccurred(QString errorString);

    // qml methods
    void setButtonText(QString buttonText);
    void setListViewItem(QString itemName);
    void qmlButtonPressed(QString textInputText);
    void qmlListViewItemClicked(QString itemText);
    QString getTheme();

signals:
};

#endif // CLIENTGUI_H
