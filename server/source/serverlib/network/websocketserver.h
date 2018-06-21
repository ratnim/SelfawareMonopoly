#pragma once

#include <QHostAddress>
#include <QWebSocketServer>

#include <models/accountmodel.h>
#include <routes/route.h>
#include <routes/routefactory.h>

class WebSocketServer : public QWebSocketServer
{
public:
    WebSocketServer(QHostAddress::SpecialAddress host = QHostAddress::AnyIPv4);

protected:
    void acccept();

    RouteFactory m_connectionFactory;
};
