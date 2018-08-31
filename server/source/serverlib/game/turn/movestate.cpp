#include "movestate.h"

#include <QJsonArray>

#include <game/dices.h>
#include <game/game.h>
#include <game/turn/idlestate.h>
#include <game/turn/possiblerequest.h>

MoveState::MoveState(TurnState* state)
    : TurnState(*state)
{
    broadcastPossibleRequests();
}

void MoveState::requestRollDice(const QString& playerName)
{
    ensurePlayersTurn(playerName);
    auto& player = m_game->currentPlayer();

	Dices dices = m_game->doCurrentPlayerRollDices();
	if (dices.isDouble())
	{
        player.canRoll(true);
	}

	if (player.timesRolled() >= 3 && dices.isDouble())
	{
        m_game->doCurrentPlayerGoToJail();
	}
    else
	{
        m_game->doCurrentPlayerMove(dices.sum());
	}
}

void MoveState::requestPossibleRequests(const QString& playerName)
{
    QJsonArray requests;

    if (playersTurn(playerName))
    {
        requests.append(PossibleRequest::rollDice().toJson());
    }

    emit m_game->onPossibleRequests(playerName, requests);
}
