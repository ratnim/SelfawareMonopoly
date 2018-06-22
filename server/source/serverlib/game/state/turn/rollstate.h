#pragma once

#include <game/state/turn/movestate.h>

class RollState : public MoveState
{
public:
    RollState(TurnState* state, int rollCount = 0);

    void rollDice() override;

protected:
    int m_rollCount;
};
