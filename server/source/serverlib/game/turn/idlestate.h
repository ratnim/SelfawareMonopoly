#pragma once

#include <game/turn/turnstate.h>

class IdleState : public TurnState
{
public:
    void requestPossibleRequests(const QString& playerName) override;

    IdleState(TurnState* state);

    void requestEndTurn(const QString& playerName) override;
};
