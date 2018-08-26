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

	Dices dices = m_game->currentPlayerRollDices();
    m_game->onRollDice(playerName, dices.first, dices.second);

	if (player.timesRolled() >= 3 && dices.isDouble())
	{
        m_game->jailCurrentPlayer();
        m_game->stateChange<IdleState>();
	}
    else
	{
	    player.move(dices.sum());
	    m_game->onPlayerMove(playerName, dices.sum());

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
