#pragma once

#include <game/jail.h>
#include <game/state/active/buddhist.h>

class Roll : public Buddhist
{
public:
    Roll(Player& player, Jail& jail);

protected:
    Player& m_player;
    Jail& m_jail;

    Buddhist* die() override;
    void handle(ActiveAction) override;
    std::vector<ActiveAction> possibleActions() const;
};