#include "gameroute.h"

#include <models/accountmodel.h>
#include <models/gamemodel.h>

GameRoute::GameRoute(QWebSocket* socket, const Request& request)
    : Route(socket)
    , m_playerName(AccountModel::instance().username(request.session))
    , m_game(GameModel::instance().openGame(request.gameId))
{
}
