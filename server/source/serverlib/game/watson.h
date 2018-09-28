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
    void requestGatherWatsonCoin(const QString& playerName, int amount, const QString& source);

	void doHarmCurrentPlayer();
    void doManipulateNextRoll(const QString& playerName, Dices dices);
    void doManipulateNextRoll(const QString& playerName, int x, int y);
    void doAddWatsonCoins(const QString& playerName, int coins);
	void doUseCoinsForMoney(const QString&, int money);

    Dices getManipulatedDices(const QString& playerName);
    int availableMoneyForCoins(const QString& playerName);
    int availableCoins(const QString& playerName);

	bool diceAreManipulated(const QString& playerName) const;
    bool currentPlayerRequest(const QString& playerName) const;	

    static int coinsToMoney(int coins);
    static int coinsForMoneyNeeded(int money);

protected:
    void createCoinAccountIfNotExisting(const QString& playerName);
	
	static const int course = 50;

    Game* m_game;
    std::map<QString, Dices> m_manipulatedDices;
    std::map<QString, int> m_coins;
};
