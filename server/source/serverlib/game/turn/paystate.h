#pragma once

#include <vector>

#include <game/turn/turnstate.h>
#include <utils/exception.h>

struct Debt
{
    Debt()
        : debtor(""), beneficiary(""), amount()
    {
        throw Exception("Debt cant be created without debtor.", Error::InternalError);
    }

    Debt(const QString& debtor, const QString& beneficiary, int amount)
        : debtor(debtor), beneficiary(beneficiary), amount(amount)
    {
    }

    QString debtor;
    QString beneficiary;
    int amount;
};

class PayState : public TurnState
{
public:
    PayState(TurnState* state, std::vector<Debt> debts);

    void requestPossibleRequests(const QString& playerName) override;
    void requestPayDebt(const QString& debtor, const QString& beneficiary) override;

protected:
    void payDebt(int debtIndex) const;
    void removeDebt(int debtIndex);
    bool debtsOpen() const;
    int findDebtIndex(const QString& debtor, const QString& beneficiary) const;

    std::vector<Debt> m_debts;
};
