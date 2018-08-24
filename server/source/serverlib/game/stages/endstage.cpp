#include "endstage.h"

#include <game/game.h>

EndState::EndState(TurnState* state)
    : TurnState(*state)
{
    emit m_game->onGameEnd();
}
