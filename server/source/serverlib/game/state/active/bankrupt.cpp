#include "bankrupt.h"

#include <game/state/active/roll.h>

Bankrupt::Bankrupt(Player& player)
    : m_player(player)

{
}

Buddhist* Bankrupt::die()
{
    return new Bankrupt(m_player);
}

void Bankrupt::handle(ActiveAction)
{
}

std::vector<ActiveAction> Bankrupt::possibleActions() const
{
    return {};
}
