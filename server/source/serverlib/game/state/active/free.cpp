#include "free.h"

Free::Free(Player& player)
    : m_player(player)

{
}

Buddhist* Free::die()
{
    return new Free(m_player);
}

void Free::handle(ActiveAction action)
{
}

std::vector<ActiveAction> Free::possibleActions() const
{
    return { ActiveAction::END_TURN };
}
