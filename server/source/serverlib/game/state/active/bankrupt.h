#pragma once

#include <game/jail.h>
#include <game/state/active/buddhist.h>

class Bankrupt : public Buddhist
{
public:
    Bankrupt(Player& player, Jail& jail);

protected:
    Player& m_player;
    Jail& m_jail;

    bool m_payed = false;

    Buddhist* die() override;
    void handle(ActiveAction) override;
    std::vector<ActiveAction> possibleActions() const;
};
