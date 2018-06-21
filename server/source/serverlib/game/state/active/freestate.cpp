#include "freestate.h"

#include <game/game.h>

FreeState::FreeState(PlayerState* state)
    : PlayerState(*state)
{
}

void FreeState::endTurn()
{
    end();
}
