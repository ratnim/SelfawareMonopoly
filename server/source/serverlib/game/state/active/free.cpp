#include "free.h"

Free::Free(Player& player, Jail& jail)
    : m_player(player)
    , m_jail(jail)
{
}

Buddhist* Free::die()
{
    return new Free(m_player, m_jail);
}

void Free::handle(ActiveAction action)
{
}

std::vector<ActiveAction> Free::possibleActions() const
{
    return { ActiveAction::END_TURN };
}
