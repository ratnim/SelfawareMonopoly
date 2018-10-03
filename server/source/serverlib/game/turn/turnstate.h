#pragma once

#include <vector>

#include <QString>

class Game;

class TurnState
{
public:
    TurnState(Game* game);
    virtual ~TurnState() = default;

    virtual void requestPossibleRequests(const QString& playerName);

    virtual void requestGameStart();

    virtual void requestPlayerReady(const QString& playerName);
    virtual void requestPlayerJoin(const QString& playerName);

    virtual void requestRollDice(const QString& playerName);
	  virtual void requestEndTurn(const QString& playerName);
	virtual void requestBuyField(const QString& playerName, bool buy);
    virtual void requestChangeHouses(const QString& playerName, const std::vector<std::pair<int,int>>& newLevels);
    virtual void requestPayDebt(const QString& debtor, const QString& beneficiary);

    void changeToDefaultState();
protected:
    Game* m_game;

	bool playersTurn(const QString& playerName) const;
    void ensurePlayersTurn(const QString& playerName) const;

    virtual void broadcastPossibleRequests();

private:
    static void InvalidRequest();
};
