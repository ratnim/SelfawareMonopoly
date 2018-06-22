#pragma once

#include <game/dices.h>
#include <game/state/turn/turnstate.h>

class MoveState : public TurnState
{
public:
    MoveState(TurnState* state);

protected:
    void goToJail();
    void movePlayer(int distance, bool canRollAgain = false, int rollCount = 1);
    Dices roll();
};
