#pragma once

#include <game/turn/turnstate.h>

class PayState : public TurnState
{
public:
    PayState(TurnState* state);
};
