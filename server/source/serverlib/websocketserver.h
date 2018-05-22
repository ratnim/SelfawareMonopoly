#pragma once

#include <set>

#include <QWebSocketServer>

#include <route.h>

struct Request
{
    static Request fromUrl(const QString& url);

    const QString route;
    const QString session;
    const QString gameId;
};

class WebSocketServer : public QWebSocketServer
{
public:
    WebSocketServer();

protected:
    void acccept();
    static void invalidRoute(const QString& route, QWebSocket* socket);

    std::map<QString, std::unique_ptr<Route>> m_routes;
};
