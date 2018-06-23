#pragma once

#include <game/state/gamestate.h>

class EndState : public GameState
{
public:
    EndState(GameState* old, Game* game);
};
