#pragma once

#include <game/jail.h>
#include <game/state/active/buddhist.h>

#include <game/dices.h>

class Roll : public Buddhist
{
public:
    Roll(Player& player);

    Buddhist* die() override;
    void handle(ActiveAction) override;
    std::vector<ActiveAction> possibleActions() const;

	void watsonRoll(const Dices& result);

protected:
    Player& m_player;

    bool m_moved = false;
    bool m_rolled = false;

	void rollDices();
    void handleResult(const Dices& result);
};
