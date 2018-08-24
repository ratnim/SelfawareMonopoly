#pragma once

#include <game/gamelogic.h>
#include <game/watson.h>

#include <game/turn/turnstate.h>

class StartState : public TurnState
{
public:
	StartState(TurnState* state, std::vector<Player> players);
};
