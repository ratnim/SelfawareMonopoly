#include "freestate.h"

#include <game/game.h>


FreeState::FreeState(TurnState* state)
    : TurnState(*state)
{
}

void FreeState::endTurn()
{
    //m_logic->end();
}
