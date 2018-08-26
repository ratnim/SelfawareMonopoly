#pragma once

#include <game/turn/turnstate.h>

class IdleState : public TurnState
{
public:
    void possibleRequests(const QString& playerName) override;

    IdleState(TurnState* state);

    void endTurn(const QString& playerName) override;
};
