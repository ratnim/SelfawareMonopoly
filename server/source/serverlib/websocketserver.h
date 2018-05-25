#pragma once

#include <set>

#include <QWebSocketServer>

#include <database.h>
#include <overviewstate.h>
#include <route.h>

struct Request
{
    static Request fromUrl(const QString& url);

    const QString route;
    const QString session;
    const QString gameId;
};

struct State
{
    OverviewState overview;
};

class WebSocketServer : public QWebSocketServer
{
public:
    WebSocketServer();

protected:
    void acccept();
    static void invalidRoute(const QString& route, QWebSocket* socket);

    State m_state;
    std::map<QString, std::unique_ptr<Route>> m_routes;
};
