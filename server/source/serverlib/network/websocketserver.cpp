#include "websocketserver.h"

#include <QMetaMethod>
#include <QWebSocket>

#include <network/request.h>

#include <routes/gameroute.h>
#include <routes/lobbyroute.h>
#include <routes/overviewroute.h>

WebSocketServer::WebSocketServer()
    : QWebSocketServer("Monopoly", QWebSocketServer::NonSecureMode)
{
    connect(this, &QWebSocketServer::newConnection, this, &WebSocketServer::acccept);

    setMaxPendingConnections(1024);
    listen(QHostAddress::Any, 31415);

    qDebug() << "Listen on port 31415";
}

void WebSocketServer::acccept()
{
    auto socket = nextPendingConnection();
    m_connectionFactory.handle(socket);
}
