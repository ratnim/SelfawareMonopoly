#include "reborn.h"

#include <game/state/active/pay.h>
#include <game/state/active/roll.h>

Reborn::Reborn(Player& player)
    : m_player(player)

{
    player.nextTurn();
}

Buddhist* Reborn::die()
{
    if (m_player.jail().needToPay())
        return new Pay(m_player);

    return new Roll(m_player);
}

void Reborn::handle(ActiveAction)
{
}

std::vector<ActiveAction> Reborn::possibleActions() const
{
    return {};
}
