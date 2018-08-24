#pragma once

#include <game/dices.h>
#include <game/gamelogic.h>

class TurnState
{
public:
    TurnState(GameLogic* logic);
    virtual ~TurnState() = default;

    virtual void possibleRequests(const QString& playerName);

	virtual void startGame();

    virtual void playerReady(const QString& playerName);
    virtual void playerJoin(const QString& playerName);

    virtual void rollDice(const QString& playerName);
    virtual void endTurn(const QString& playerName);

protected:
    GameLogic* m_logic;

	QJsonObject createPossibleRequest(const QString& requestName) const;

private:
    static void InvalidRequest();
};
