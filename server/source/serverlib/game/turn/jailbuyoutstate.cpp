#include "jailbuyoutstate.h"

#include <QJsonArray>

#include <game/dices.h>
#include <game/game.h>
#include <game/turn/idlestate.h>
#include <game/turn/possiblerequest.h>

#include <utils/exception.h>

JailBuyoutState::JailBuyoutState(TurnState* state, const Dices& roll)
    : TurnState(*state)
    , m_dices(roll)
{
    broadcastPossibleRequests();
}

void JailBuyoutState::requestPossibleRequests(const QString& playerName)
{
    QJsonArray requests;

    if (playersTurn(playerName))
    {
        requests.append(PossibleRequest::payDebt("", 50).toJson());

        // TODO: How to get number of attempts?
        if (m_game->currentPlayer().timesRolled() < 3)
        {
            requests.append(PossibleRequest::endTurn().toJson());
        }
    }

    emit m_game->onPossibleRequests(playerName, requests);
}

void JailBuyoutState::requestPayDebt(const QString& debtor, const QString& beneficiary)
{
    ensurePlayersTurn(debtor);

    if (beneficiary != "")
    {
        throw Exception("Invalid beneficiary", Error::InvalidRequest);
    }

    // TODO: Out-of-jail card
    m_game->doTransferMoney(debtor, beneficiary, 50);

    m_game->currentPlayer().leaveJail();

    m_game->doCurrentPlayerMove(m_dices.sum());
}

void JailBuyoutState::requestEndTurn(const QString& playerName)
{
    ensurePlayersTurn(playerName);

    // Delegate request to prevent inconsistencies
    m_game->stateChange<IdleState>();

    m_game->requestEndTurn(playerName);
}
