#pragma once 

#include <game/state/active/buddhist.h>
#include <game/jail.h>

class Reborn : public Buddhist
{
public:
    Reborn(Player& player);

protected:
    Player& m_player;

    Buddhist* die() override;
    void handle(ActiveAction) override;
    std::vector<ActiveAction> possibleActions() const;
};
