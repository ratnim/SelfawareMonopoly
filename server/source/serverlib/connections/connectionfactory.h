#pragma once
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QWebSocket>

#include <network/connectionrequest.h>
#include <connections/connection.h>

class ConnectionFactory
{
public:
    using Factory = void (ConnectionFactory::*)(QWebSocket*, const ConnectionRequest&);

    ConnectionFactory();

    void handle(QWebSocket* socket);
    static void disconnect(QWebSocket* socket);

protected:
    template <class ConnectionHandler>
    void create(QWebSocket* socket, const ConnectionRequest& request)
    {
        auto handler = new ConnectionHandler(socket, request);

        QObject::connect(socket, &QWebSocket::textMessageReceived, handler, &Connection::incommingMessage);
        QObject::connect(socket, &QWebSocket::readChannelFinished, [socket] { disconnect(socket); });
    }

    Factory routeFactory(const QString& routeName) const;

    static std::map<QString, Factory> routes();

    const std::map<QString, Factory> m_routes;
};
