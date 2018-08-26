#pragma once

#include <game/turn/turnstate.h>

class JailState : public TurnState
{
public:
    JailState(TurnState* state);

	void possibleRequests(const QString& playerName) override;
    void rollDice(const QString& playerName) override;
};
