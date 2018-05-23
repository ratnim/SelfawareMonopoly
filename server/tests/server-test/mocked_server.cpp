#include "mocked_server.h"

#include <thread>

#include <QWebSocket>

std::unique_ptr<QCoreApplication> MockedServer::app;
std::unique_ptr<MockedServer> MockedServer::srv;

MockedServer::MockedServer()
    : QWebSocketServer("monopoly testing", QWebSocketServer::NonSecureMode)
{
    setMaxPendingConnections(1024);
    listen(QHostAddress::LocalHost, 31416);

    qDebug() << "Listen on port 31416";
}

MockedServer::Connection MockedServer::createConnection()
{
    // Create a client socket
    auto socket = std::make_unique<QWebSocket>();
    socket->open(QUrl("ws://localhost:31416/"));

    // Get the server socket
    while (!hasPendingConnections())
    {
        application().processEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return std::make_pair(std::move(socket), WebSocket(nextPendingConnection()));
}

QCoreApplication& MockedServer::application()
{
    return *app;
}

MockedServer& MockedServer::server()
{
    return *srv;
}

void MockedServer::constructServer(int argc, char** argv)
{
    app = std::make_unique<QCoreApplication>(argc, argv);
    srv = std::make_unique<MockedServer>();
}
