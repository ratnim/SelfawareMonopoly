#include "overviewroute.h"

#include <QJsonDocument>

OverviewRoute::OverviewRoute(QWebSocket* socket, const Request& request)
    : Route(socket)
{
    m_actions["enter_lobby"] = synchronCallback(socket, m_createAccount);
}
