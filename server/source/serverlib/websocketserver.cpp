#include "websocketserver.h"

#include <QMetaMethod>
#include <QUrlQuery>
#include <QWebSocket>

#include <game.h>
#include <lobby.h>
#include <overview.h>

WebSocketServer::WebSocketServer()
    : QWebSocketServer("Monopoly", QWebSocketServer::NonSecureMode)
{
    connect(this, &QWebSocketServer::newConnection, this, &WebSocketServer::acccept);

    m_routes[""] = std::make_unique<Overview>();
    m_routes["lobby"] = std::make_unique<Lobby>();
    m_routes["game"] = std::make_unique<Game>();

    setMaxPendingConnections(1024);
    listen(QHostAddress::Any, 31415);

    qDebug() << "Listen on port 31415";
}

void WebSocketServer::acccept()
{
    auto socket = nextPendingConnection();
    auto resource_name = socket->resourceName().split('/').back();

    qDebug() << resource_name;

    auto& route = m_routes.find(resource_name);
    if (route == m_routes.end())
    {
        invalidRoute(resource_name, socket);
    }
    else
    {
        route->second->mount(socket);
    }
}

void WebSocketServer::invalidRoute(const QString& route, QWebSocket* socket)
{
    const auto error = QString("Invalid Route: '%1'.").arg(route);
    socket->sendTextMessage(Route::generateError(error, Route::InvalidRoute));
    socket->flush();
    socket->close();
    socket->deleteLater();
}