#pragma once

#include <set>

#include <QWebSocketServer>

#include <models/accountmodel.h>
#include <routes/route.h>
#include <routes/routefactory.h>

class WebSocketServer : public QWebSocketServer
{
public:
    WebSocketServer();

protected:
    void acccept();

    RouteFactory m_connectionFactory;
};
