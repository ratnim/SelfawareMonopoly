#pragma once

#include <game/turn/turnstate.h>
#include <game/dices.h>

class JailBuyoutState : public TurnState
{
public:
    JailBuyoutState(TurnState* state, const Dices& roll);

	void requestPossibleRequests(const QString& playerName) override;
    void requestPayDebt(const QString& debtor, const QString& beneficiary) override;
    void requestEndTurn(const QString& playerName) override;

protected:
    const Dices m_dices;
};
