#include "idlestate.h"

#include <QJsonArray>

#include <game/game.h>
#include <game/turn/jailstate.h>
#include <game/turn/movestate.h>
#include <game/turn/possiblerequest.h>

IdleState::IdleState(TurnState* state)
    : TurnState(*state)
{
    broadcastPossibleRequests();
}

void IdleState::requestPossibleRequests(const QString& playerName)
{
    QJsonArray requests;

    if (playersTurn(playerName))
    {
        requests.append(PossibleRequest::endTurn().toJson());
        if (m_game->board().isGroupOwner(playerName))
        {
            requests.append(PossibleRequest::constructBuilding().toJson());
        }
    }

    emit m_game->onPossibleRequests(playerName, requests);
}

void IdleState::requestEndTurn(const QString& playerName)
{
    ensurePlayersTurn(playerName);

    m_game->players().next();
    m_game->currentPlayer().nextTurn();
    emit m_game->onTurnChange(m_game->currentPlayer().name());

    if (m_game->currentPlayer().inJail())
    {
        m_game->stateChange<JailState>();
    }
    else
    {
        m_game->stateChange<MoveState>();
    }
}

void IdleState::requestChangeHouses(const QString& playerName, const std::vector<std::pair<int, int>>& newLevels)
{
    ensurePlayersTurn(playerName);

    m_game->doCurrentPlayerChangeHouses(newLevels);
}