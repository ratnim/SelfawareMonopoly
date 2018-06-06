#include "routefactory.h"

#include <QJsonDocument>

#include <routes/gameroute.h>
#include <routes/lobbyroute.h>
#include <routes/overviewroute.h>
#include <routes/route.h>
#include <utils/exception.h>

RouteFactory::RouteFactory()
{
    m_routes[""] = &RouteFactory::create<OverviewRoute>;
    m_routes["lobby"] = &RouteFactory::create<LobbyRoute>;
    m_routes["game"] = &RouteFactory::create<GameRoute>;
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
    socket->close();
    socket->deleteLater();
}

RouteFactory::Factory RouteFactory::routeFactory(const QString& routeName) const
{
    auto& route = m_routes.find(routeName);
    if (route == m_routes.end())
    {
        throw Exception(QString("Invalid Route: '%1'.").arg(routeName), Exception::InvalidRoute);
    }
    return route->second;
}
