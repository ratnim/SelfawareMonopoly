#include "idlestate.h"

#include <game/game.h>


IdleState::IdleState(TurnState* state)
    : TurnState(*state)
{
}

void IdleState::endTurn()
{
    //m_logic->end();
}
