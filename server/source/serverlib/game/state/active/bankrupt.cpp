#include "bankrupt.h"

#include <game/state/active/roll.h>

Bankrupt::Bankrupt(Player& player, Jail& jail)
    : m_player(player)
    , m_jail(jail)
{
}

Buddhist* Bankrupt::die()
{
    return new Bankrupt(m_player, m_jail);
}

void Bankrupt::handle(ActiveAction)
{
}

std::vector<ActiveAction> Bankrupt::possibleActions() const
{
    return {};
}
