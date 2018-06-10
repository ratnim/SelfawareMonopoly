#include "roll.h"

#include <game/state/active/field.h>
#include <game/state/active/free.h>

Roll::Roll(Player& player, Jail& jail)
    : m_player(player)
    , m_jail(jail)
{
}

Buddhist* Roll::die()
{
    if (m_moved)
        return new Field(m_player, m_jail);
    if (m_rolled)
        return new Free(m_player, m_jail);

    return new Roll(m_player, m_jail);
}

void Roll::handle(ActiveAction action)
{
    switch (action)
    {
    case ActiveAction::ROLL_DICE:
        rollDices();
    }
}

std::vector<ActiveAction> Roll::possibleActions() const
{
    return { ActiveAction::ROLL_DICE };
}

void Roll::rollDices()
{
    handleResult({});
}

void Roll::watsonRoll(const Dices& dices)
{
    handleResult(dices);
}

void Roll::handleResult(const Dices& dices)
{
    m_rolled = true;
    ++m_player.rolled;

    if (m_jail.inJail())
    {
        if (m_jail.escape(dices))
        {
            // move
            m_moved = true;
        }
    }
    else
    {
        if (dices.isDouble() && m_player.rolled == 3)
        {
            m_jail.jail();
        }
        else
        {
            if (dices.isDouble())
            {
                m_player.canRoll = true;
            }
            // move
            m_moved = true;
        }
    }
}
