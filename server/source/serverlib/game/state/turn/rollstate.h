#pragma once

#include <game/state/turn/turnstate.h>

class RollState : public TurnState
{
public:
    RollState(TurnState* state, GameLogic* logic);
    RollState(TurnState* state, int rollCount = 0);

    void rollDice() override;

protected:
    int m_rollCount;
};
