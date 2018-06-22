#include "jailstate.h"

#include <game/state/runstate.h>
#include <game/state/turn/freestate.h>

JailState::JailState(TurnState* state)
    : MoveState(state)
{
}

void JailState::rollDice()
{
    auto d = roll();
    
    if (d.isDouble())
    {
        movePlayer(d.sum());
    }
    else
    {
        m_state->stateChange<FreeState>(this);
    }
}
