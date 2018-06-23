#include "rollstate.h"

#include <game/dices.h>
#include <game/game.h>

RollState::RollState(PlayerState* state, GameLogic* logic)
    : PlayerState(logic)
{
}

RollState::RollState(PlayerState* state, int rollCount)
    : PlayerState(*state)
    , m_rollCount(rollCount)
{
}

void RollState::rollDice()
{
    auto d = m_logic->roll();

    ++m_rollCount;
    if (m_rollCount == 3)
    {
        m_logic->goToJail();
    }
    else
    {
        m_logic->movePlayer(d.sum(), d.isDouble(), m_rollCount);
    }
}
