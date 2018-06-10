#pragma once

#include <vector>

#include <game/player.h>
#include <game/state/active/activeaction.h>

class Buddhist
{
public:
    virtual Buddhist* die() = 0;
    virtual void handle(ActiveAction action) = 0;
    virtual std::vector<ActiveAction> possibleActions() const = 0;
};
