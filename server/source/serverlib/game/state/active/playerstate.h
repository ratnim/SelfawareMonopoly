#pragma once

#include <game/player.h>
#include <utils/ringbuffer.h>

class Game;
class RunState;

class PlayerState
{
public:
    PlayerState(Game* game, RunState* state, RingBuffer<Player>& player);

    virtual void rollDice();
    virtual void endTurn();

protected:
    void end();

    Game* m_game;
    RunState* m_state;
    RingBuffer<Player>& m_player;

private:
    static void InvalidRequest();
};
