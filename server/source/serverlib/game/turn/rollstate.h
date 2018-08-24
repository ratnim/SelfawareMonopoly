#pragma once

#include <game/turn/turnstate.h>

class RollState : public TurnState
{
public:
    RollState(TurnState* state);
    RollState(TurnState* state, int rollCount);

    virtual void rollDice();

protected:
    int m_rollCount;
};
