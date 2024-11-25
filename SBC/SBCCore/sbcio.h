#ifndef SBCIO_H
#define SBCIO_H

#include <QObject>
#include <QDebug>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <gpiod.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/spi/spidev.h>


class SBCIO : public QObject
{
    Q_OBJECT
public:
    explicit SBCIO(QObject *parent = nullptr);

    void setGPIO(int gpioPin);
    void setI2C(int pin);

signals:
    void sigErrorOccurred(QString errorString);

};

#endif // SBCIO_H
