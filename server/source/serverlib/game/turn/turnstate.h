#pragma once

#include <game/dices.h>
#include <game/gamelogic.h>

class Game;

class TurnState
{
public:
    TurnState(Game* game);
	TurnState(GameLogic* logic);
    virtual ~TurnState() = default;

    virtual void possibleRequests(const QString& playerName);

	virtual void gameStart();

    virtual void playerReady(const QString& playerName);
    virtual void playerJoin(const QString& playerName);

    virtual void rollDice(const QString& playerName);
    virtual void endTurn(const QString& playerName);

protected:
    GameLogic* m_logic;
    Game* m_game;

private:
    static void InvalidRequest();
};
