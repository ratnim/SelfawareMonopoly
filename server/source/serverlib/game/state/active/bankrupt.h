#pragma once

#include <game/jail.h>
#include <game/state/active/buddhist.h>

class Bankrupt : public Buddhist
{
public:
    Bankrupt(Player& player);

protected:
    Player& m_player;

    bool m_payed = false;

    Buddhist* die() override;
    void handle(ActiveAction) override;
    std::vector<ActiveAction> possibleActions() const;
};
