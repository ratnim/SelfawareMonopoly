#include <game/turn/paystate.h>

#include <QJsonArray>

#include <game/turn/possiblerequest.h>
#include <game/turn/idlestate.h>

#include <game/game.h>

#include <utils/exception.h>

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

    requests.append(PossibleRequest::fileBankruptcy().toJson());

    emit m_game->onPossibleRequests(playerName, requests);
}

void PayState::requestPayDebt(const QString& debtor, const QString& beneficiary)
{
    auto debtIndex = findDebtIndex(debtor, beneficiary);
    payDebt(debtIndex);
    removeDebt(debtIndex);
    if (!debtsOpen())
    {
        changeToDefaultState();
    }
}

void PayState::requestFileBankruptcy(const QString& playerName)
{
    // Assuming only single beneficiary
    bool playerHasDebt = false;
    QString beneficiary;
    for (auto& debt : m_debts)
    {
        if (debt.debtor == playerName)
        {
            playerHasDebt = true;
            beneficiary = debt.beneficiary;
            break;
        }
    }

    if (!playerHasDebt)
    {
        throw Exception("Player has no depts", Error::InvalidRequest);
    }

    // Transfer posessions
    m_game->doFileBankruptcy(playerName, beneficiary);

    // If it was his turn, move on to the next player automatically
    if (m_game->currentPlayer().name() == playerName)
    {
        m_game->stateChange<IdleState>();
        m_game->requestEndTurn(playerName);
    }

    m_game->playerLost(playerName);
}

int PayState::findDebtIndex(const QString& debtor, const QString& beneficiary) const
{
    for (int i = 0; i < m_debts.size(); ++i)
    {
        if (m_debts[i].debtor == debtor && m_debts[i].beneficiary == beneficiary)
        {
            return i;
        }
    }

    throw Exception(QString("No debt for debtor: '%1' and beneficiary '%2'found.").arg(debtor, beneficiary));
}

void PayState::payDebt(int debtIndex) const
{
    m_game->doTransferMoney(m_debts[debtIndex].debtor, m_debts[debtIndex].beneficiary, m_debts[debtIndex].amount);
}

void PayState::removeDebt(int debtIndex)
{
    m_debts[debtIndex] = m_debts[m_debts.size() - 1];
    m_debts.resize(m_debts.size() - 1);
}

bool PayState::debtsOpen() const
{
    return m_debts.size() > 0;
}
