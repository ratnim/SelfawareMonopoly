#include "routefactory.h"

#include <QJsonDocument>

#include <routes/gameroute.h>
#include <routes/lobbyroute.h>
#include <routes/overviewroute.h>
#include <utils/exception.h>

RouteFactory::RouteFactory()
    : m_routes(routes())
{
}

void RouteFactory::handle(QWebSocket* socket)
{
    auto request = Request::fromUrl(socket->resourceName());

    try
    {
        auto routeConstructor = routeFactory(request.route);
        (this->*routeConstructor)(socket, request);
    }
    catch (const Exception &e)
    {
        socket->sendTextMessage(e.json());
        disconnect(socket);
    }
}

void RouteFactory::disconnect(QWebSocket* socket)
{
    socket->flush();
    socket->deleteLater();
}

RouteFactory::Factory RouteFactory::routeFactory(const QString& routeName) const
{
    const auto& route = m_routes.find(routeName);
    if (route == m_routes.end())
    {
        throw Exception(QString("'%1' is not valid.").arg(routeName), error::InvalidRoute);
    }
    return route->second;
}

std::map<QString, RouteFactory::Factory> RouteFactory::routes()
{
    std::map<QString, RouteFactory::Factory> routes;
    routes[QString("")] = &RouteFactory::create<OverviewRoute>;
    routes[QString("lobby")] = &RouteFactory::create<LobbyRoute>;
    routes[QString("game")] = &RouteFactory::create<GameRoute>;

    return routes;
}
