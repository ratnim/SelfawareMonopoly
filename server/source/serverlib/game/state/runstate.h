#pragma once

#include <game/gamelogic.h>
#include <game/watson.h>
#include <game/state/gamestate.h>
#include <game/state/turn/turnstate.h>
#include <utils/budhist.h>

class RunState : public GameState, public Budhist<TurnState>
{
public:
    RunState(Game* game, std::vector<Player> players);

    RingBuffer<Player>& players();
    Watson& watson();

    void rollDice(const QString& playerName) override;
    void endTurn(const QString& playerName) override;

protected:
    void checkPlayer(const QString& playerName);

    RingBuffer<Player> m_players;
    Watson m_watson;
    GameLogic m_logic;
};
