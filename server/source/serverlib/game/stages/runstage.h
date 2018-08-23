#pragma once

#include <game/gamelogic.h>
#include <game/watson.h>
#include <game/stages/stage.h>
#include <game/turn/turnstate.h>
#include <utils/budhist.h>

class RunStage : public Stage, public Budhist<TurnState>
{
public:
    RunStage(Game* game, std::vector<Player> players);

    Player& player();
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
