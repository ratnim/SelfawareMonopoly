#include "endstate.h"

#include <game/game.h>

EndState::EndState(Game* game)
{
    emit game->onGameEnd();
}
