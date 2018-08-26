#include "idlestate.h"

#include <game/game.h>


IdleState::IdleState(TurnState* state)
    : TurnState(*state)
{
    broadcastPossibleRequests();
}

void IdleState::endTurn()
{
    //m_logic->end();
}
