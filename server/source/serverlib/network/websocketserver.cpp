#include "websocketserver.h"

#include <QMetaMethod>
#include <QWebSocket>

#include <network/connectionrequest.h>

#include <connections/gameconnection.h>
#include <connections/lobbyconnection.h>
#include <connections/overviewconnection.h>

WebSocketServer::WebSocketServer(QHostAddress::SpecialAddress host)
    : QWebSocketServer("Monopoly", QWebSocketServer::NonSecureMode)
{
    connect(this, &QWebSocketServer::newConnection, this, &WebSocketServer::acccept);

    setMaxPendingConnections(1024);
    listen(host, 31415);
    
    qDebug() << "Listen on port 31415";
}

void WebSocketServer::acccept()
{
    auto socket = nextPendingConnection();
    m_connectionFactory.handle(socket);
}
