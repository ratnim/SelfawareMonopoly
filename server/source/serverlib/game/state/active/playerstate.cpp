#include "playerstate.h"

#include <utils/exception.h>

PlayerState::PlayerState(GameLogic* logic)
    : m_logic(logic)
{
}

void PlayerState::rollDice()
{
    InvalidRequest();
}

void PlayerState::endTurn()
{
    InvalidRequest();
}

void PlayerState::InvalidRequest()
{
    throw Exception("You are not allowed to perform this action.", error::InvalidRequest);
}
