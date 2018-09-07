#pragma once

#include <map>

#include <QString>

#include <game/dices.h>

class Game;

class Watson
{
public:
    Watson(Game * game);

    void requestAddClick(const QString& playerName, const QString& addName);
    void requestScannedGMailAccount(const QString& playerName, Dices dices);

	void doHarmCurrentPlayer();
    void doManipulateNextRoll(const QString& playerName, Dices dices);
    void doManipulateNextRoll(const QString& playerName, int x, int y);

    Dices getManipulatedDices(const QString& playerName);

	bool diceAreManipulated(const QString& playerName) const;
    bool currentPlayerRequest(const QString& playerName) const;	

protected:
    Game* m_game;
    std::map<QString, Dices> m_manipulatedDices;
};
