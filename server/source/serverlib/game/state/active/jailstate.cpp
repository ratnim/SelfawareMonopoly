#include "jailstate.h"

#include <game/state/runstate.h>
#include <game/state/active/freestate.h>

JailState::JailState(PlayerState* state)
    : PlayerState(*state)
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
