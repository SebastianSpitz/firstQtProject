#include <QCoreApplication>
#include <clientcore.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Check if there are enough arguments
    if (argc < 3) {
        qDebug() << "Usage: SBCConsole <command> <parameter>";
        return 1;
    }

    // Parse the arguments
    QString command = argv[1];
    QString parameter = argv[2];

    qDebug() << "Command:" << command;
    qDebug() << "Parameter:" << parameter;

    // Example action based on command and parameter
    if (command == "commandxy") {
        // Perform action with the parameter
        qDebug() << "Executing commandxy with parameter:" << parameter;
        ClientCore core;
    } else {
        qDebug() << "Unknown command:" << command;
    }

    return a.exec();
}
