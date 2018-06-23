#include "endstate.h"

#include <game/game.h>

EndState::EndState(GameState* old, Game* game)
{
    emit game->onGameEnd();
}
