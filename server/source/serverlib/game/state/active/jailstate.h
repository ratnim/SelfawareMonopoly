#pragma once

#include <game/state/active/playerstate.h>

class JailState : public PlayerState
{
public:
    JailState(PlayerState* state);

    void rollDice() override;
};
