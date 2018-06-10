#include "pay.h"

#include <game/state/active/roll.h>
#include <game/state/active/bankrupt.h>

Pay::Pay(Player& player)
    : m_player(player)

{
}

Buddhist* Pay::die()
{
    if (m_payed)
        return new Roll(m_player);

    return new Bankrupt(m_player);
}

void Pay::handle(ActiveAction action)
{
	switch (action)
	{
    case ActiveAction::PAY:
        m_payed = true;
        return;
	}
}

std::vector<ActiveAction> Pay::possibleActions() const
{
    return { ActiveAction::PAY };
}
