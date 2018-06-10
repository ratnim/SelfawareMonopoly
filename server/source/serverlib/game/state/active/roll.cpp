#include "roll.h"

Roll::Roll(Player& player, Jail& jail)
    : m_player(player)
    , m_jail(jail)
{
}

Buddhist* Roll::die()
{
    return new Roll(m_player, m_jail);
}

void Roll::handle(ActiveAction action)
{
}

std::vector<ActiveAction> Roll::possibleActions() const
{
    return {};
}
