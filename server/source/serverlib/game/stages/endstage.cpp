#include "endstage.h"

#include <game/game.h>

EndStage::EndStage(Game* game)
{
    emit game->onGameEnd();
}
