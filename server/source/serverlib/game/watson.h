#pragma once

#include <queue>

#include <QString>

#include <game/dices.h>

class Game;

class Watson
{
public:
    Watson(Game * game);

    void requestAddClick(const QString& playerName, const QString& addName);
    
	void doHarmCurrentPlayer();
    void doManipulateNextRoll(Dices dices);
    void doManipulateNextRoll(int x, int y);

    Dices getManipulatedDices();

	bool diceAreManipulated() const;
    bool currentPlayerRequest(const QString& playerName) const;	

protected:
    void clearRolls();

    Game* m_game;
    std::queue<Dices> m_nextRolls;
};
