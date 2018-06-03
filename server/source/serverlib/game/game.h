#pragma once

#include <vector>

#include <QObject>
#include <QString>

class Game : public QObject
{
    Q_OBJECT

public:
    enum State
    {
        START,
        RUNNING,
        FINISHED
    };

    const std::vector<QString>& players() const;
    State state() const;

    void join(const QString& playerName);
    void ready(const QString& playerName);
    void start();

    void rollDice(const QString& playerName);
    void endTurn(const QString& playerName);

signals:
    void onPlayerJoin(const QString &playerName);
    void onPlayerReady(const QString& playerName);

    void onGameStart();
    void onGameEnd();

    void onRollDice(int d1, int d2);
    void onPlayerMove(int distance);
    void onTurnChange(const QString& newMovingPlayer);

protected:
    State m_state;
    std::vector<QString> m_players;
};
