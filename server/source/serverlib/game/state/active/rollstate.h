#pragma once

#include <game/state/active/playerstate.h>

class RollState : public PlayerState
{
public:
    RollState(PlayerState* state, GameLogic* logic);
    RollState(PlayerState* state, int rollCount = 0);

    void rollDice() override;

protected:
    int m_rollCount;
};
