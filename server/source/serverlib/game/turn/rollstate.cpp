#include "rollstate.h"

#include <QJsonArray>

#include <game/game.h>
#include <game/dices.h>
#include <game/turn/idlestate.h>
#include <game/turn/possiblerequest.h>
#include <utils/exception.h>

RollState::RollState(TurnState* state)
    : TurnState(*state)
{
    broadcastPossibleRequests();
}

void RollState::rollDice(const QString& playerName)
{
    if (!playersTurn(playerName))
    {
        throw Exception("Not your turn.", Error::InvalidRequest);
    }

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

void RollState::possibleRequests(const QString& playerName)
{
    QJsonArray requests;

    if (playersTurn(playerName))
    {
        requests.append(PossibleRequest::rollDice().toJson());
    }

    emit m_game->onPossibleRequests(playerName, requests);
}
