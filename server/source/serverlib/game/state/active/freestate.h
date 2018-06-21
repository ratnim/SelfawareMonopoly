#pragma once

#include <game/state/active/playerstate.h>

class FreeState : public PlayerState
{
public:
    FreeState(PlayerState* state);

    void endTurn() override;
};
