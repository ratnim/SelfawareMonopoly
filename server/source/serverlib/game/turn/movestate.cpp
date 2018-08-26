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

	Dices dices = m_game->getDices();

    m_game->onRollDice(playerName, dices.first, dices.second);

	m_game->currentPlayer().move(dices.sum());
    m_game->onPlayerMove(playerName, dices.sum());

    //++m_rollCount;
    //if (m_rollCount == 3)
    //{
    //    m_logic->goToJail();
    //}
    //else
    //{
    //    m_logic->movePlayer(d.sum(), d.isDouble(), m_rollCount);
    //}

    m_game->stateChange<IdleState>();
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
