#include "connectionfactory.h"

#include <QJsonDocument>

#include <connections/gameconnection.h>
#include <connections/lobbyconnection.h>
#include <connections/overviewconnection.h>
#include <utils/exception.h>

ConnectionFactory::ConnectionFactory()
    : m_routes(routes())
{
}

void ConnectionFactory::handle(QWebSocket* socket)
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

void ConnectionFactory::disconnect(QWebSocket* socket)
{
    socket->flush();
    socket->deleteLater();
}

ConnectionFactory::Factory ConnectionFactory::routeFactory(const QString& routeName) const
{
    const auto& route = m_routes.find(routeName);
    if (route == m_routes.end())
    {
        throw Exception(QString("'%1' is not valid.").arg(routeName), Error::InvalidRoute);
    }
    return route->second;
}

std::map<QString, ConnectionFactory::Factory> ConnectionFactory::routes()
{
    std::map<QString, ConnectionFactory::Factory> routes;
    routes[QString("")] = &ConnectionFactory::create<OverviewConnection>;
    routes[QString("lobby")] = &ConnectionFactory::create<LobbyConnection>;
    routes[QString("game")] = &ConnectionFactory::create<GameConnection>;

    return routes;
}
