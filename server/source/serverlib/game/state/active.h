#pragma once

#include <game/jail.h>
#include <game/state/state.h>

class Passive;

class Active : public State
{
    friend Passive;

public:
    Active(Passive old);

	void rollDice();
    void endTurn();

protected:
    Jail m_jail;

    bool m_canRoll;
    int m_rolled;

};
