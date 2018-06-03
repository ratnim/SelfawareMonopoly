#pragma once

#include <actions/action.h>
#include <game/game.h>

class GameAction : public Action
{
public:
    GameAction(const QString& playerName, Game& game);

protected:
    const QString m_playerName;
    Game& m_game;
};
