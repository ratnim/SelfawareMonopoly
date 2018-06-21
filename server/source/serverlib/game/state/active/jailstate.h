#pragma once

#include <game/state/active/movestate.h>

class JailState : public MoveState
{
public:
    JailState(PlayerState* state);

    void rollDice() override;
};
