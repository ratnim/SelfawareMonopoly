#pragma once

#include <QHostAddress>
#include <QWebSocketServer>

#include <models/accountmodel.h>
#include <connections/connection.h>
#include <connections/connectionfactory.h>

class WebSocketServer : public QWebSocketServer
{
public:
    WebSocketServer(QHostAddress::SpecialAddress host = QHostAddress::AnyIPv4);

protected:
    void acccept();

    ConnectionFactory m_connectionFactory;
};
