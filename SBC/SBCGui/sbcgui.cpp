#include "sbcgui.h"

SBCGui::SBCGui(QObject *parent, QmlInterface *qmlInterface)
    : QObject{parent}
{
    core = new SBCCore(this);
    //qmlInterface = QmlInterface::getInstance();
    qDebug() << qmlInterface;
    connect(qmlInterface, &QmlInterface::sigSignal, this, &SBCGui::testMethod);
}

void SBCGui::testMethod()
{
    qDebug() << "test method called!";
}
