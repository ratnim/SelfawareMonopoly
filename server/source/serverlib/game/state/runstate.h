#pragma once

#include <game/gamelogic.h>
#include <game/state/gamestate.h>
#include <game/state/turn/turnstate.h>
#include <utils/budhist.h>

class RunState : public GameState, public Budhist<TurnState>
{
public:
    RunState(Game* game, std::vector<Player> players);

    void rollDice(const QString& playerName) override;
    void endTurn(const QString& playerName) override;

protected:
    void checkPlayer(const QString& playerName);

    RingBuffer<Player> m_players;
    GameLogic m_logic;
};
