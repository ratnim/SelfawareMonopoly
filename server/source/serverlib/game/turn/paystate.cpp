#include <game/turn/paystate.h>

#include <QJsonArray>

#include <game/turn/possiblerequest.h>	

#include <game/game.h>

PayState::PayState(TurnState* state, std::vector<Debt> debts)
    : TurnState(*state)
    , m_debts(debts)
{
    broadcastPossibleRequests();
}

void PayState::requestPossibleRequests(const QString& playerName)
{
    QJsonArray requests;

    for (const auto& debt : m_debts)
    {
		if (debt.debtor == playerName)
		{
			requests.append(PossibleRequest::payDebt(debt.beneficiary, debt.amount).toJson());
		}
    }

    emit m_game->onPossibleRequests(playerName, requests);
}
