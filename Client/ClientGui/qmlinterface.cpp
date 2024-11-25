#include "qmlinterface.h"

QmlInterface::QmlInterface(QObject *parent)
    : QObject{parent}
{
    qDebug() << "QmlInterface constructor called! Singleton created.";
}

QmlInterface *QmlInterface::getInstance() {
    static QmlInterface instance;
    return &instance;
}

void QmlInterface::buttonPressed(QString textInputString)
{
    emit sigButtonPressed(textInputString);
}

void QmlInterface::listViewItemClicked(QString itemString)
{
    emit sigListViewItemClicked(itemString);
}

void QmlInterface::settingsButtonClicked()
{
    qDebug() << "Settings button was clicked";
}

void QmlInterface::connectionButtonClicked()
{
    qDebug() << "Bluetooth button was clicked";
}


void QmlInterface::setButtonText(QString buttonText)
{
    emit sigNewButtonText(buttonText);
}

void QmlInterface::setListViewItem(QString itemName)
{
    emit sigNewListViewItem(itemName);
}

QString QmlInterface::getTheme()
{
    qDebug() << "getTheme()";
    return "dark";
}


