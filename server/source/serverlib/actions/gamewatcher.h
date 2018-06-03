#pragma once

#include <QJsonArray>
#include <QJsonObject>

#include <actions/watcher.h>
#include <game/game.h>

class GameWatcher : public Watcher
{
public:
    GameWatcher(const Game &game);

protected:
    void playerMove(int distance);
    void gameEnd();

    static QJsonObject toJson(int gameId);
    static QJsonArray toArray(const std::vector<QString>& players);

    static QString moveAnswer(int distance);
    static QString gameEndAnswer();

    const Game& m_game;
};
