#include <iostream>

#include <utils/configuration.h>
#include <network/websocketserver.h>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    Configuration conv(app);

    WebSocketServer api;

    return app.exec();
}
