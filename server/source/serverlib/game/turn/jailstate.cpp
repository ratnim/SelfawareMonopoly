#include "jailstate.h"

#include <game/turn/startstate.h>
#include <game/turn/freestate.h>


JailState::JailState(TurnState* state)
    : TurnState(*state)
{
}

void JailState::rollDice()
{
    //auto d = m_logic->roll();

    //if (d.isDouble())
    //{
    //    m_logic->movePlayer(d.sum());
    //}
    //else
    //{
    //    m_logic->idle();
    //}
}
