#include "overviewroute.h"

#include <QJsonDocument>

OverviewRoute::OverviewRoute(QWebSocket* socket, const Request& request)
    : Route(socket)
{
    m_actions["enter_LobbyRoute"] = makeCallback(socket, m_createAccount);
}
