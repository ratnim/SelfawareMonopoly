#pragma once

#include <game/dices.h>
#include <game/game.h>
#include <game/player.h>
#include <utils/ringbuffer.h>

class RunState;

class GameLogic
{
public:
    GameLogic(Game* game, RunState* state);

    void goToJail();
    void movePlayer(int distance, bool canRollAgain = false, int rollCount = 1);
    Dices roll();

    void free();
    void end();

protected:
    Game* m_game;
    RunState* m_state;
    RingBuffer<Player>& m_players;
    Watson& m_watson;
};
