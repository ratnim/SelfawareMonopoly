#pragma once

#include <game/jail.h>
#include <game/state/active/buddhist.h>

class Pay : public Buddhist
{
public:
    Pay(Player& player);

protected:
    Player& m_player;

	bool m_payed = false;

    Buddhist* die() override;
    void handle(ActiveAction) override;
    std::vector<ActiveAction> possibleActions() const;
};
