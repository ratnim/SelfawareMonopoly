#pragma once

#include <game/turn/turnstate.h>

class RollState : public TurnState
{
public:
    RollState(TurnState* state);

	void possibleRequests(const QString& playerName) override;
    void rollDice(const QString& playerName) override;

protected:
    void broadcastPossibleRequests();
};
