#pragma once 

#include <vector>

#include <game/player.h>
#include <game/state/active/activeaction.h>

class Buddhist
{
public:
    Buddhist die();
    void handle(ActiveAction action);
    std::vector<ActiveAction> possibleActions();

protected:
	Buddhist(Player& player) : m_player(player){};
    Player& m_player;
};
