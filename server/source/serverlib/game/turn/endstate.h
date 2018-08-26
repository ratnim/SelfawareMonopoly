#pragma once

#include <game/turn/turnstate.h>

class EndState : public TurnState
{
public:
    EndState(TurnState* state);
};
