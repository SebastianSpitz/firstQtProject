#include "logger.h"

Logger* Logger::getInstance()
{
    static Logger logger;
    return &logger;
}

Logger::Logger(QObject* parent)
    : QObject{parent}
{
    m_currentDate = QDate::currentDate().toString("yyyyMMdd");
    openLogFile();
}

Logger::~Logger()
{
    if (m_logFile.isOpen()) {
        m_logFile.close();
    }
}

void Logger::openLogFile()
{
    // Ensure the logs directory exists
    QDir logDir("logs");
    if (!logDir.exists()) {
        logDir.mkpath(".");
    }

    QString logFileName = QString("logs/log_%1.txt").arg(m_currentDate);
    m_logFile.setFileName(logFileName);

    if (!m_logFile.open(QIODevice::Append | QIODevice::Text)) {
        // Handle error opening the file
    }
}

void Logger::checkDate()
{
    QString currentDate = QDate::currentDate().toString("yyyyMMdd");
    if (currentDate != m_currentDate) {
        // Date has changed; open a new log file
        if (m_logFile.isOpen()) {
            m_logFile.close();
        }
        m_currentDate = currentDate;
        openLogFile();
    }
}

void Logger::logMessage(const QString& message, const QString& severity)
{
    checkDate();

    if (m_logFile.isOpen()) {
        QTextStream out(&m_logFile);
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        out << "[" << timestamp << "] [" << severity << "] " << message << "\n";
        out.flush();
    } else {
        // Handle error: file is not open
    }
}

void Logger::logError(const QString& message)
{
    logMessage(message, "ERROR");
}

void Logger::logInfo(const QString& message)
{
    logMessage(message, "INFO");
}

void Logger::logWarning(const QString& message)
{
    logMessage(message, "WARNING");
}

void Logger::logDebug(const QString& message)
{
    logMessage(message, "DEBUG");
}
