#pragma once

#include <game/state/gamestate.h>
#include <game/state/active/playerstate.h>
#include <utils/budhist.h>
#include <utils/ringbuffer.h>

class RunState : public GameState, public Budhist<PlayerState>
{
public:
    RunState(Game* game, std::vector<Player> players);

    void rollDice(const QString& playerName) override;
    void endTurn(const QString& playerName) override;

protected:
    void checkPlayer(const QString& playerName);

    Game* m_game;
    RingBuffer<Player> m_player;
};
