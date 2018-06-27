#pragma once

#include <game/dices.h>
#include <game/gamelogic.h>

class TurnState
{
public:
    TurnState(GameLogic* logic);
    virtual ~TurnState() = default;

    virtual void rollDice();
    virtual void endTurn();

protected:
    GameLogic* m_logic;

private:
    static void InvalidRequest();
};
