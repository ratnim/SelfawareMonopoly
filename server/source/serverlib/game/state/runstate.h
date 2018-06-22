#pragma once

#include <game/state/gamestate.h>
#include <game/state/turn/turnstate.h>
#include <utils/budhist.h>
#include <utils/ringbuffer.h>

class RunState : public GameState, public Budhist<TurnState>
{
public:
    RunState(Game* game, std::vector<Player> players);

    void rollDice(const QString& playerName) override;
    void endTurn(const QString& playerName) override;

protected:
    Game* m_game;
    RingBuffer<Player> m_players;
};
