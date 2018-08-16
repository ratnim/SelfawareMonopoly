#pragma once

#include <game/state/turn/turnstate.h>

class RollState : public TurnState
{
public:
    RollState(TurnState* state, GameLogic* logic);
    RollState(TurnState* state, int rollCount = 0);

    virtual void rollDice();

protected:
    int m_rollCount;
};
