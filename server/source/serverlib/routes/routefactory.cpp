#include "routefactory.h"

#include <QJsonDocument>

#include <routes/game.h>
#include <routes/lobby.h>
#include <routes/overview.h>
#include <routes/playercommunication.h>

RouteFactory::RouteFactory()
{
    m_routes[""] = create<Overview>;
    m_routes["lobby"] = create<Lobby>;
    m_routes["game"] = create<Game>;
}

void RouteFactory::handle(QWebSocket* socket)
{
    auto request = Request::fromUrl(socket->resourceName());

    auto routeConstructor = routeFactory(request.route);
    (this->*routeConstructor)(socket, request);

    // TODO catch exceptions here
}

void RouteFactory::error(QWebSocket* socket, const Request& request)
{
    // TODO throw exceptions in here
    const auto error = QString("Invalid Route: '%1'.").arg(request.route);
    socket->sendTextMessage(PlayerCommunication::toString(PlayerCommunication::generateError(error, PlayerCommunication::InvalidRoute)));
    socket->flush();
    socket->close();
    socket->deleteLater();
}

RouteFactory::Factory RouteFactory::routeFactory(const QString& routeName)
{
    auto& route = m_routes.find(routeName);
    if (route == m_routes.end())
    {
        return error;
    }
    return route->second;
}