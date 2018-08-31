#include <game/turn/paystate.h>

PayState::PayState(TurnState* state, std::vector<Debt> debts)
    : TurnState(*state)
    , m_debts(debts)
{
    broadcastPossibleRequests();
}
