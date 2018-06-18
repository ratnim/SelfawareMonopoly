#pragma once

#include <map>
#include <vector>

#include <QObject>
#include <QString>

#include <actions/gamewatcher.h>

#include <game/player.h>

class Game : public QObject
{
    Q_OBJECT

public:
    Game();

    enum State
    {
        START,
        RUNNING,
        FINISHED
    };

    void join(const QString& playerName);
    void ready(const QString& playerName);
    void start();

    void rollDice(const QString& playerName);
    void endTurn(const QString& playerName);

signals:
    void onPlayerJoin(const QString& playerName);
    void onPlayerReady(const QString& playerName);

    void onGameStart();
    void onGameEnd();

    void onRollDice(int d1, int d2);
    void onPlayerMove(const QString& playerName, int distance);
    void onTurnChange(const QString& newMovingPlayer);

protected:
    void goToJail(const QString& playerName);

    const QString m_label;

    State m_state;
    std::map<QString, Player> m_players;
    std::vector<QString> m_turnOrder;
    int m_turn;
    bool canRoll;
    int reRollCount;
};
