#pragma once
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QWebSocket>

#include <network/request.h>

class RouteFactory
{
public:
    using Factory = void (RouteFactory::*)(QWebSocket*, const Request&);

    RouteFactory();

    void handle(QWebSocket* socket);
    static void disconnect(QWebSocket* socket);

protected:
    template <class ConnectionHandler>
    void create(QWebSocket* socket, const Request& request)
    {
        auto handler = new ConnectionHandler(socket, request);

        QObject::connect(socket, &QWebSocket::textMessageReceived, handler, &Route::incommingMessage);
        QObject::connect(socket, &QWebSocket::readChannelFinished, [socket] { disconnect(socket); });
    }

    Factory routeFactory(const QString& routeName) const;

    std::map<QString, Factory> m_routes;
};
