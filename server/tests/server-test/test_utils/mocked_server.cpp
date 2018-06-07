#include "mocked_server.h"

#include <thread>

#include <QWebSocket>

std::unique_ptr<QCoreApplication> MockedServer::app;
std::unique_ptr<WebSocketServer> MockedServer::srv;

QCoreApplication& MockedServer::application()
{
    return *app;
}

WebSocketServer& MockedServer::server()
{
    return *srv;
}

void MockedServer::constructServer(int argc, char** argv)
{
    app = std::make_unique<QCoreApplication>(argc, argv);
    srv = std::make_unique<WebSocketServer>(QHostAddress::LocalHost);
}
