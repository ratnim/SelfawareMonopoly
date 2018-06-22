#include "rollstate.h"

#include <game/dices.h>
#include <game/game.h>

RollState::RollState(PlayerState* state, int rollCount)
    : PlayerState(*state)
    , m_rollCount(rollCount)
{
}

void RollState::rollDice()
{
    auto d = roll();

    ++m_rollCount;
    if (m_rollCount == 3)
    {
        goToJail();
    }
    else
    {
        movePlayer(d.sum(), d.isDouble(), m_rollCount);
    }
}
