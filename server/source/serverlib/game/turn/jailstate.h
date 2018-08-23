#pragma once

#include <game/turn/turnstate.h>

class JailState : public TurnState
{
public:
    JailState(TurnState* state);

    virtual void rollDice();
};
