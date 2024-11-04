#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT

public:
    static Logger *getInstance();

private:
    explicit Logger(QObject *parent = nullptr);
    ~Logger();

};

#endif // LOGGER_H
