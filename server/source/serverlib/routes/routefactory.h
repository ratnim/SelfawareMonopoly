#pragma once
#include <QJsonObject>
#include <QString>
#include <QWebSocket>

#include <network/request.h>

class RouteFactory
{
public:
    using Factory = void (RouteFactory::*)(QWebSocket*, const Request&);

    RouteFactory();

    void handle(QWebSocket* socket);

protected:
    template <class Connection>
    void create(QWebSocket* socket, const Request& request)
    {
        new Connection(socket, request);
    }

    Factory routeFactory(const QString& routeName) const;

    std::map<QString, Factory> m_routes;
};
