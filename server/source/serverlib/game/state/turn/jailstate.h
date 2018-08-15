#pragma once

#include <game/state/turn/turnstate.h>

class JailState : public TurnState
{
public:
    JailState(TurnState* state);

    virtual void rollDice();
};
