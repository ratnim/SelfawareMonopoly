#include "turnstate.h"

#include <game/game.h>
#include <game/state/runstate.h>
#include <game/state/turn/jailstate.h>
#include <game/state/turn/rollstate.h>
#include <utils/exception.h>

TurnState::TurnState(GameLogic* logic)
    : m_logic(logic)
{
}

void TurnState::rollDice()
{
    InvalidRequest();
}

void TurnState::endTurn()
{
    InvalidRequest();
}

void TurnState::InvalidRequest()
{
    throw Exception("You are not allowed to perform this action.", Error::InvalidRequest);
}
