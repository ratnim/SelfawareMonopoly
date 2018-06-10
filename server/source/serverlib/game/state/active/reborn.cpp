#include "reborn.h"

#include <game/state/active/pay.h>
#include <game/state/active/roll.h>

Reborn::Reborn(Player& player, Jail& jail)
    : m_player(player)
    , m_jail(jail)
{
    m_jail.nextTurn();
}

Buddhist* Reborn::die()
{
    if (m_jail.needToPay())
        return new Pay(m_player, m_jail);

    return new Roll(m_player, m_jail);
}

void Reborn::handle(ActiveAction)
{
}

std::vector<ActiveAction> Reborn::possibleActions() const
{
    return {};
}
