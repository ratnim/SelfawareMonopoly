#include "field.h"

#include <game/state/active/free.h>
#include <game/state/active/roll.h>

Field::Field(Player& player, Jail& jail)
    : m_player(player)
    , m_jail(jail)
{
}

Buddhist* Field::die()
{
    if (m_player.canRoll)
		return new Roll(m_player, m_jail);

	return new Free(m_player, m_jail);
}

void Field::handle(ActiveAction action)
{
}

std::vector<ActiveAction> Field::possibleActions() const
{
    return {};
}
