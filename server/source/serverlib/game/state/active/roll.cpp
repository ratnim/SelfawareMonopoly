#include "roll.h"

#include <game/state/active/field.h>
#include <game/state/active/free.h>

Roll::Roll(Player& player)
    : m_player(player)

{
}

Buddhist* Roll::die()
{
    if (m_moved)
        return new Field(m_player);
    if (m_rolled)
        return new Free(m_player);

    return new Roll(m_player);
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

    if (m_player.jail().inJail())
    {
        if (m_player.jail().escape(dices))
        {
            // move
            m_moved = true;
        }
    }
    else
    {
        if (dices.isDouble() && m_player.rolled == 3)
        {
            m_player.jail().jail();
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
