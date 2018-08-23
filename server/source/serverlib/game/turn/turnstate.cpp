#include "turnstate.h"

#include <game/game.h>
#include <game/stages/runstage.h>
#include <game/turn/jailstate.h>
#include <game/turn/rollstate.h>
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
