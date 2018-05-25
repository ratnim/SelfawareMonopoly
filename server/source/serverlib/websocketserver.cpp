#include "websocketserver.h"

#include <QMetaMethod>
#include <QWebSocket>

#include <game.h>
#include <lobby.h>
#include <overview.h>
#include <request.h>

WebSocketServer::WebSocketServer()
    : QWebSocketServer("Monopoly", QWebSocketServer::NonSecureMode)
{
    connect(this, &QWebSocketServer::newConnection, this, &WebSocketServer::acccept);

    m_routes[""] = std::make_unique<Overview>(m_overview);
    m_routes["lobby"] = std::make_unique<Lobby>(m_overview);
    m_routes["game"] = std::make_unique<Game>();

    setMaxPendingConnections(1024);
    listen(QHostAddress::Any, 31415);

    qDebug() << "Listen on port 31415";
}

void WebSocketServer::acccept()
{
    auto socket = nextPendingConnection();
    auto request = Request::fromUrl(socket->resourceName());

    auto& route = m_routes.find(request.route);
    if (route == m_routes.end())
    {
        invalidRoute(request.route, socket);
    }
    else
    {
        // TODO it is possible to add the request object here.
        route->second->mount(socket, request);
    }
}

void WebSocketServer::invalidRoute(const QString& route, QWebSocket* socket)
{
    const auto error = QString("Invalid Route: '%1'.").arg(route);
    socket->sendTextMessage(Route::toString(Route::generateError(error, Route::InvalidRoute)));
    socket->flush();
    socket->close();
    socket->deleteLater();
}
