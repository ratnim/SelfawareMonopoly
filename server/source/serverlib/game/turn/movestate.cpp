#include "movestate.h"

#include <QJsonArray>

#include <game/game.h>
#include <game/dices.h>
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

    Dices dice;
    m_game->onRollDice(playerName, dice.first, dice.second);

	m_game->currentPlayer().move(dice.sum());
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
