#pragma once

#include <game/turn/turnstate.h>

class JailState : public TurnState
{
public:
    JailState(TurnState* state);

	void requestPossibleRequests(const QString& playerName) override;
    void requestRollDice(const QString& playerName) override;
};
