#pragma once

#include <game/turn/turnstate.h>

class FreeState : public TurnState
{
public:
    FreeState(TurnState* state);

    virtual void endTurn();
};
