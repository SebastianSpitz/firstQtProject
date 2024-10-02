#include "sbcio.h"

SBCIO::SBCIO(QObject *parent)
    : QObject{parent}
{
    qDebug() << "sbc io created";
}
