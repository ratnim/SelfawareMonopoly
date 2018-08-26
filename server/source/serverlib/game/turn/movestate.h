#pragma once

#include <game/turn/turnstate.h>

class MoveState : public TurnState
{
public:
    MoveState(TurnState* state);

	void possibleRequests(const QString& playerName) override;
    void rollDice(const QString& playerName) override;

protected:
	

};
