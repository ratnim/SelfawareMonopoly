#pragma once

#include <QCoreApplication>

#include <network/websocketserver.h>

class MockedServer
{
public:
    using WebSocket = std::unique_ptr<QWebSocket>;
    using Connection = std::pair<WebSocket, WebSocket>;

    static QCoreApplication& application();
    static WebSocketServer& server();

    static void constructServer(int argc, char** argv);

protected:
    static std::unique_ptr<QCoreApplication> app;
    static std::unique_ptr<WebSocketServer> srv;
};