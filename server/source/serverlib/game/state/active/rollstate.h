#pragma once

#include <game/state/active/movestate.h>

class RollState : public MoveState
{
public:
    RollState(PlayerState* state, int rollCount = 0);

    void rollDice() override;

protected:
    int m_rollCount;
};
