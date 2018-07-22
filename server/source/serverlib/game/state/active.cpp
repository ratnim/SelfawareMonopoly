#include "active.h"

#include <game/dices.h>
#include <game/state/passive.h>
#include <utils/exception.h>

Active::Active(Passive& old)
    : State(old)
    , m_jail(old.m_jail)
{
    m_jail.nextTurn();
    if (m_jail.needToPay())
    {
        //m_player.
    }
}

void Active::rollDice()
{
    if (!m_canRoll)
    {
        throw Exception("Player can't roll dice.");
    }

    Dices dices;

    //m_player.roll(dices.first, dices.second);

    m_canRoll = false;
    ++m_rolled;

    if (!m_jail.inJail())
    {
        if (dices.isDouble())
        {
            if (m_rolled >= 3)
            {
                m_jail.jail();
                //m_player.goToJail();
            }
            else
            {
                m_canRoll = true;
            }
        }
    }
    else
    {
        if (m_jail.escape(dices))
        {
            //m_player.escape();
        }
    }

    if (!m_jail.inJail())
    {
        //m_player.move(dices.first + dices.second);
    }
}

void Active::endTurn()
{
}
