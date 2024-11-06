#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QString>
#include <QDateTime>
#include <QTextStream>
#include <QDir>

class Logger : public QObject
{
    Q_OBJECT

public:
    static Logger* getInstance();

    // Methods for logging different types of messages
    void logError(const QString& message);
    void logInfo(const QString& message);
    void logWarning(const QString& message);
    void logDebug(const QString& message);

private:
    explicit Logger(QObject* parent = nullptr);
    ~Logger();

    void logMessage(const QString& message, const QString& severity);
    void checkDate();
    void openLogFile();

    QFile m_logFile;
    QString m_currentDate;
};

#endif // LOGGER_H
