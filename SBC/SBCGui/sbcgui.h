#ifndef SBCGUI_H
#define SBCGUI_H

#include <QObject>
#include <sbccore.h>

#include "qmlinterface.h"

class SBCGui : public QObject
{
    Q_OBJECT

public:
    explicit SBCGui(QObject *parent = nullptr, QmlInterface *qmlInterface = nullptr);
    void testMethod();

private:
    //QmlInterface *qmlInterface;
    SBCCore *core;

signals:

};

#endif // SBCGUI_H
