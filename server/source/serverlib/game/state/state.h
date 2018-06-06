#pragma once

class Player;
class Enter;

class State
{
protected:
    State(Player& player) : m_player(player){};

    Player& m_player;
};
