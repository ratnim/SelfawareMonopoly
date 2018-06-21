#pragma once

#include <QObject>
#include <QString>

class Game;

class GameState
{
public:
    virtual void join(const QString& playerName);
    virtual void ready(const QString& playerName);
    virtual void start();

    virtual void rollDice(const QString& playerName);
    virtual void endTurn(const QString& playerName);

private:
    static void InvalidRequest();
};
