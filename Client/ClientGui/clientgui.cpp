#include "clientgui.h"

// Constructor
ClientGui::ClientGui(QObject *parent, QmlInterface *qmlInterface)
    : QObject{parent}
{
    this->qmlInterface = qmlInterface;
    connect(qmlInterface, &QmlInterface::sigButtonPressed, this, &ClientGui::qmlButtonPressed);
    connect(qmlInterface, &QmlInterface::sigListViewItemClicked, this, &ClientGui::qmlListViewItemClicked);

    this->clientCore = new ClientCore(this);
    connect(clientCore, &ClientCore::sigServerFound, this, &ClientGui::coreServerFound);
    connect(clientCore, &ClientCore::sigConnected, this, &ClientGui::coreConnected);
    connect(clientCore, &ClientCore::sigDisconnected, this, &ClientGui::coreDisconnected);
    connect(clientCore, &ClientCore::sigDataReceived, this, &ClientGui::coreDataReceived);
    connect(clientCore, &ClientCore::sigErrorOccurred, this, &ClientGui::coreErrorOccurred);

    qmlInterface->setButtonText("Welcome to Miami");
    qmlInterface->setListViewItem("Ay papi");
}

// Public methods
void ClientGui::connectToServer(QString serverName)
{

}

void ClientGui::searchServer()
{

}

void ClientGui::sendData(QVariant data)
{

}

// Private methods core
void ClientGui::coreServerFound(QString serverName)
{

}

void ClientGui::coreConnected(QString serverName)
{

}

void ClientGui::coreDisconnected(QString serverName)
{

}

void ClientGui::coreDataReceived(QVariant data)
{

}

void ClientGui::coreErrorOccurred(QString errorString)
{

}

// Private methods qml
void ClientGui::setButtonText(QString buttonText)
{
    qmlInterface->setButtonText(buttonText);
}

void ClientGui::setListViewItem(QString itemName)
{
    qmlInterface->setListViewItem(itemName);
}

void ClientGui::qmlButtonPressed(QString textInputText)
{
    qDebug() << "Qml send button was pressed: " + textInputText;
}

void ClientGui::qmlListViewItemClicked(QString itemText)
{
    qDebug() << "Qml listViewItem was clicked: " + itemText;
}

QString ClientGui::getTheme()
{
    // QSettings stores settings in the correct OS path
    QSettings settings("Spitz", "ClientGui");

    qDebug() << "getTheme in ClientGui called";

    // return the value of "theme" if there is no value than return the default value "dark"
    return settings.value("theme", "dark").toString();
}

