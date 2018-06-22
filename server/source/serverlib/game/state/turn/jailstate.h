#pragma once

#include <game/state/turn/movestate.h>

class JailState : public MoveState
{
public:
    JailState(TurnState* state);

    void rollDice() override;
};
