#pragma once

#include <game/dices.h>
#include <game/gamelogic.h>

class PlayerState
{
public:
    PlayerState(GameLogic* logic);

    virtual void rollDice();
    virtual void endTurn();

protected:
    GameLogic* m_logic;

private:
    static void InvalidRequest();
};
