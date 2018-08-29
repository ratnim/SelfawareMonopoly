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

void MoveState::rollDice(const QString& playerName)
{
    ensurePlayersTurn(playerName);
    auto& player = m_game->currentPlayer();

	Dices dices = m_game->doCurrentPlayerRollDices();

	if (player.timesRolled() >= 3 && dices.isDouble())
	{
        m_game->doJailCurrentPlayer();
        m_game->stateChange<IdleState>();
	}
    else
	{
        m_game->doMoveCurrentPlayer(dices.sum());

		if (player.position() == m_game->GO_TO_JAIL_POSITION)
		{
            m_game->stateChange<IdleState>();
		}
		else if (dices.isDouble())
		{
            m_game->stateChange<MoveState>();
		}
		else
		{
			m_game->stateChange<IdleState>();
		}
	}
}

void MoveState::possibleRequests(const QString& playerName)
{
    QJsonArray requests;

    if (playersTurn(playerName))
    {
        requests.append(PossibleRequest::rollDice().toJson());
    }

    emit m_game->onPossibleRequests(playerName, requests);
}
