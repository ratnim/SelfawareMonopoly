#pragma once

#include <set>

#include <QWebSocketServer>

#include <models/accountmodel.h>
#include <routes/playercommunication.h>
#include <routes/routefactory.h>

class WebSocketServer : public QWebSocketServer
{
public:
    WebSocketServer();

protected:
    void acccept();

    AccountModel m_accounts;
    RouteFactory m_connectionFactory;
};
