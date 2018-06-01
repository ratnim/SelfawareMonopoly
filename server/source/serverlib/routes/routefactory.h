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
        // TODO throw exceptions in here
        new Connection(socket, request);
    }

    void error(QWebSocket* socket, const Request& request);
    Factory routeFactory(const QString& routeName);

    std::map<QString, Factory> m_routes;
    QObject* m_parent;
};
