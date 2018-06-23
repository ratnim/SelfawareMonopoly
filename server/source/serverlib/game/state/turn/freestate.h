#pragma once

#include <game/state/turn/turnstate.h>

class FreeState : public TurnState
{
public:
    FreeState(TurnState* state);

    void endTurn() override;
};
