#pragma once

#include <QJsonArray>
#include <QJsonObject>

#include <actions/watcher.h>

class Game;

class GameWatcher : public Watcher
{
public:
    GameWatcher(const Game& game);

    const std::vector<QString>& messages() const;

protected:
    void event(const QString &message);

    void playerJoin(const QString& playerName);
    void playerReady(const QString& playerName);

    void rollDice(int d1, int d2);
    void playerMove(const QString& playerName, int distance);
    void changeTurn(const QString& movingPlayer);

    void gameStart();
    void gameEnd();

    static QString toString(const QJsonObject& object);

    const Game& m_game;
    std::vector<QString> m_messages;
};
