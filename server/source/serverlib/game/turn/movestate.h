#pragma once

#include <game/turn/turnstate.h>

class MoveState : public TurnState
{
public:
    MoveState(TurnState* state);

	void requestPossibleRequests(const QString& playerName) override;
    void requestRollDice(const QString& playerName) override;
};
