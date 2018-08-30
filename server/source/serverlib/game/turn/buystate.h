#pragma once

#include <game/turn/turnstate.h>

class BuyState : public TurnState
{
public:
    BuyState(TurnState* state);

	void requestPossibleRequests(const QString& playerName) override;
};
