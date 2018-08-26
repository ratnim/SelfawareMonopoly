#pragma once

#include <QString>

class Game;

class TurnState
{
public:
    TurnState(Game* game);
    virtual ~TurnState() = default;

    virtual void possibleRequests(const QString& playerName);

    virtual void gameStart();

    virtual void playerReady(const QString& playerName);
    virtual void playerJoin(const QString& playerName);

    virtual void rollDice(const QString& playerName);
    virtual void endTurn(const QString& playerName);

protected:
    Game* m_game;

	bool playersTurn(const QString& playerName) const;

private:
    static void InvalidRequest();
};
