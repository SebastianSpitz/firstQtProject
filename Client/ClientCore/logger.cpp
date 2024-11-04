#include "logger.h"


Logger *Logger::getInstance()
{
    static Logger logger;
    return &logger;
}


Logger::Logger(QObject *parent)
    : QObject{parent}
{

}


Logger::~Logger()
{

}
