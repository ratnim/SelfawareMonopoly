#pragma once

#include <QObject>
#include <QString>

class Game;

class Stage
{
public:
    virtual ~Stage() = default;

    virtual void playerJoin(const QString& playerName);
    virtual void playerReady(const QString& playerName);
    virtual void gameStart();

    virtual void rollDice(const QString& playerName);
    virtual void endTurn(const QString& playerName);
    virtual void possibleRequests(const QString& playerName);

private:
    static void InvalidRequest();
};
