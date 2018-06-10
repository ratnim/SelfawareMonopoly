#pragma once

#include <game/jail.h>
#include <game/state/active/buddhist.h>

class Field : public Buddhist
{
public:
    Field(Player& player, Jail& jail);

    Buddhist* die() override;
    void handle(ActiveAction) override;
    std::vector<ActiveAction> possibleActions() const;

protected:
    Player& m_player;
    Jail& m_jail;
};