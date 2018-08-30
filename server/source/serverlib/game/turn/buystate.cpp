#include "buystate.h"

#include <QJsonArray>

#include <game/game.h>
#include <game/turn/possiblerequest.h>

BuyState::BuyState(TurnState* state)
    : TurnState(*state)
{
    broadcastPossibleRequests();
}

void BuyState::requestPossibleRequests(const QString& playerName)
{
    QJsonArray requests;

    if (playersTurn(playerName))
    {
        requests.append(PossibleRequest::buyField().toJson());
    }

    emit m_game->onPossibleRequests(playerName, requests);
}