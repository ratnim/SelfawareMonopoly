#pragma once

#include <QString>

#include <game/jail.h>

const int BOARD_SIZE = 36;

class Player
{
public:


    bool ready = false;
    bool canRoll = true;

    int position = 0;
    int rolled = 0;

    void nextTurn();
    Jail& jail();

protected:
    Jail m_jail;
};