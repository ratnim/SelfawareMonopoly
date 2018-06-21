#pragma once

#include <game/dices.h>

class Jail
{
public:
    void jail();
    bool inJail();
    bool needToPay();
    void nextTurn();
    bool escape(const Dices& dices);
protected:
    bool m_jailed = false;
    int m_turns = 0;
};
