#pragma once

#include <QCoreApplication>
#include <QWebSocketServer>

class MockedServer : public QWebSocketServer
{
public:
    MockedServer();

    using WebSocket = std::unique_ptr<QWebSocket>;
    using Connection = std::pair<WebSocket, WebSocket>;

    Connection createConnection();

    static QCoreApplication& application();
    static MockedServer& server();

    static void constructServer(int argc, char** argv);

protected:
    static std::unique_ptr<QCoreApplication> app;
    static std::unique_ptr<MockedServer> srv;
};