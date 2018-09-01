#include "buystate.h"

#include <QJsonArray>

#include <game/game.h>
#include <game/turn/possiblerequest.h>
#include <game/board/street.h>

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

void BuyState::requestBuyField(const QString& playerName, bool buy)
{
    ensurePlayersTurn(playerName);
    auto& player = m_game->currentPlayer();

    if (buy)
    {
        m_game->doCurrentPlayerBuyField();
        changeToDefaultState();
    }
	else
	{
        changeToDefaultState();
	}
}