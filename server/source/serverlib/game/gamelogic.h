#pragma once

#include <game/dices.h>
#include <game/player.h>
#include <game/watson.h>
#include <utils/ringbuffer.h>

class StartState;
class Game;

class GameLogic
{
public:
    GameLogic(Game* game, StartState* state);

    void goToJail();
    void movePlayer(int distance, bool canRollAgain = false, int rollCount = 1);
    Dices roll();

    void idle();
    void end();

    Game* m_game;
protected:
    void nextPlayer();
    void prepareTurnState();

    StartState* m_state;
};
