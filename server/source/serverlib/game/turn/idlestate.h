#pragma once

#include <game/turn/turnstate.h>

class IdleState : public TurnState
{
public:
    IdleState(TurnState* state);

    virtual void endTurn();
};
