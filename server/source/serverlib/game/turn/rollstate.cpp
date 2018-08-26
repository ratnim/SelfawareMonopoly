#include "rollstate.h"

#include <utils/exception.h>

#include <game/dices.h>
#include <game/game.h>
#include <game/turn/freestate.h>


RollState::RollState(TurnState* state)
    : TurnState(*state)
{
}

void RollState::rollDice(const QString& playerName)
{
	if (!playersTurn(playerName))
	{
        throw Exception("Not your turn.", Error::InvalidRequest);
	}

	Dices dice;
    m_game->onRollDice(playerName, dice.first, dice.second);
    m_game->onPlayerMove(playerName, dice.sum());

    //++m_rollCount;
    //if (m_rollCount == 3)
    //{
    //    m_logic->goToJail();
    //}
    //else
    //{
    //    m_logic->movePlayer(d.sum(), d.isDouble(), m_rollCount);
    //}

	m_game->stateChange<FreeState>();
}
