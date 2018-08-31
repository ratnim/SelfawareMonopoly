#include <game/turn/paystate.h>

PayState::PayState(TurnState* state)
    : TurnState(*state)
{
    broadcastPossibleRequests();
}
