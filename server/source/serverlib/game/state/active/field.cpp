#include "field.h"

#include <game/state/active/bankrupt.h>
#include <game/state/active/free.h>
#include <game/state/active/roll.h>

Field::Field(Player& player)
    : m_player(player)
{
}

Buddhist* Field::die()
{
    if (m_player.position >= BOARD_SIZE)
        return new Bankrupt(m_player);

    if (m_player.canRoll)
        return new Roll(m_player);

    return new Free(m_player);
}

void Field::handle(ActiveAction action)
{
}

std::vector<ActiveAction> Field::possibleActions() const
{
    return {};
}
