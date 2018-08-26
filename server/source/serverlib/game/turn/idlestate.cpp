#include "idlestate.h"

#include <QJsonArray>

#include <game/game.h>
#include <game/turn/rollstate.h>
#include <game/turn/possiblerequest.h>


IdleState::IdleState(TurnState* state)
    : TurnState(*state)
{
    broadcastPossibleRequests();
}

void IdleState::possibleRequests(const QString& playerName)
{
    QJsonArray requests;

    if (playersTurn(playerName))
    {
        requests.append(PossibleRequest::endTurn().toJson());
    }

    emit m_game->onPossibleRequests(playerName, requests);
}

void IdleState::endTurn(const QString& playerName)
{
    ensurePlayersTurn(playerName);

    m_game->players().next();
    m_game->currentPlayer().nextTurn();
    emit m_game->onTurnChange(m_game->currentPlayer().name());

	m_game->stateChange<RollState>();
}
