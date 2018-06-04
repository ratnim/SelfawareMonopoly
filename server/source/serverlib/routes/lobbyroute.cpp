#include "lobbyroute.h"

#include <actions/lobbywatcher.h>
#include <models/accountmodel.h>

#include <QJsonDocument>

LobbyRoute::LobbyRoute(QWebSocket* socket, const Request& request)
    : Route(socket)
    , m_playerName(AccountModel::instance().username(request.session))
    , m_createGame(m_playerName)
{
    connect(&LobbyWatcher::instance(), &Watcher::send, socket, &QWebSocket::sendTextMessage);
    m_actions["create_game"] = synchronCallback(socket, m_createGame);
}
