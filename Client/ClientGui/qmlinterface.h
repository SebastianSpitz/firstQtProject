#ifndef QMLINTERFACE_H
#define QMLINTERFACE_H

#include <QObject>
#include <QStringList>
#include <QQmlEngine>

#include "eventbus.h"

class QmlInterface : public QObject
{
    Q_OBJECT
    //QML_ELEMENT
    //QML_SINGLETON

public:
    static QmlInterface *getInstance();

    void setEventBus(EventBus*);

    Q_INVOKABLE void buttonPressed(QString textInputString);
    Q_INVOKABLE void listViewItemClicked(QString itemString);
    Q_INVOKABLE void settingsButtonClicked();
    Q_INVOKABLE void connectionButtonClicked();
    Q_INVOKABLE QString getTheme();

    void setButtonText(QString buttonText);
    void setListViewItem(QString itemName);

private:
    QmlInterface(QObject *parent = nullptr);

signals:
    void sigButtonPressed(QString textInputString);
    void sigListViewItemClicked(QString itemString);
    void sigNewButtonText(QString buttonText);
    void sigNewListViewItem(QString itemName);
    QString sigGetTheme();
};

#endif // QMLINTERFACE_H
