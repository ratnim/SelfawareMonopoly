#pragma once

class Player;
class Enter;

class State
{
protected:
    State(Player& player) : m_player(player){};
    State(State& state)
        : m_player(state.m_player){};

    Player& m_player;
};
