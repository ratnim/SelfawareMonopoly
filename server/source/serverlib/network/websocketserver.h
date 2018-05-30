#pragma once

#include <set>

#include <QWebSocketServer>

#include <models/accountmodel.h>
#include <routes/route.h>

class WebSocketServer : public QWebSocketServer
{
public:
    WebSocketServer();

protected:
    void acccept();
    static void invalidRoute(const QString& route, QWebSocket* socket);

    AccountModel m_accounts;
    //std::map<QString, std::unique_ptr<Route>> m_routes;
    RouteFactory m_routes;
};
