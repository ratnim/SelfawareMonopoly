#pragma once

#include <game/dices.h>
#include <game/state/active/playerstate.h>

class MoveState : public PlayerState
{
public:
    MoveState(PlayerState* state);

protected:
    void goToJail();
    void movePlayer(int distance, bool canRollAgain = false, int rollCount = 1);
    Dices roll();
};
