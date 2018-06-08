#include <iostream>

#include <network/websocketserver.h>
#include <utils/program.h>
#include <utils/configuration.h>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    Configuration conv(app);

    Program p;

    WebSocketServer api;

    return app.exec();
}
