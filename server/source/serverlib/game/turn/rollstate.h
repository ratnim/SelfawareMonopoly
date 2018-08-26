#pragma once

#include <game/turn/turnstate.h>

class RollState : public TurnState
{
public:
    RollState(TurnState* state);

    void rollDice(const QString& playerName) override;
};
