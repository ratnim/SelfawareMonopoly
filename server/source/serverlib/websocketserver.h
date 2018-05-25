#pragma once

#include <set>

#include <QWebSocketServer>

#include <accountmodel.h>
#include <route.h>

class WebSocketServer : public QWebSocketServer
{
public:
    WebSocketServer();

protected:
    void acccept();
    static void invalidRoute(const QString& route, QWebSocket* socket);

    AccountModel m_overview;
    std::map<QString, std::unique_ptr<Route>> m_routes;
};
