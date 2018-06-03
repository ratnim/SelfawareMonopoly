
#include "lobbyroute.h"

#include <models/accountmodel.h>

#include <QJsonDocument>

LobbyRoute::LobbyRoute(QWebSocket* socket, const Request& request)
    : Route(socket)
    , m_playerName(AccountModel::instance().username(request.session))
{
    connect(&m_watcher, &Watcher::send, socket, &QWebSocket::sendTextMessage);
}
