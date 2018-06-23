#pragma once

#include <map>

#include <game/player.h>
#include <game/state/gamestate.h>

class InitState : public GameState
{
public:
    InitState(GameState* state, Game* game);

    void join(const QString& playerName) override;
    void ready(const QString& playerName) override;
    void start() override;

protected:
    std::vector<Player> turnOrder();

    Game* m_game;
    std::map<QString, bool> m_playersReady;
};
