#include <iostream>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>

#include <configuration.h>
#include <websocketserver.h>

#include <thread>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    Configuration conv(app);

    WebSocketServer api;

    return app.exec();
}
