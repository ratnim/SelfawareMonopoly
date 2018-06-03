#pragma once

#include <game/game.h>
#include <routes/route.h>

class GameRoute : public Route
{
public:
    GameRoute(QWebSocket* socket, const Request& request);

protected:
    const QString m_playerName;
    Game& m_game;
};
