#pragma once

#include <vector>

#include <game/turn/turnstate.h>

struct Debt
{
	Debt(const QString& debtor, const QString& beneficiary, int amount) 
		: debtor(debtor), beneficiary(beneficiary), amount(amount)
	{
	}
    const QString debtor;
    const QString beneficiary;
    const int amount;
};

class PayState : public TurnState
{
public:
    PayState(TurnState* state, std::vector<Debt> debts);

protected:
    std::vector<Debt> m_debts;
};
