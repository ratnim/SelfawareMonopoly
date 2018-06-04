#pragma once

#include <QJsonArray>
#include <QJsonObject>

#include <actions/watcher.h>
#include <game/game.h>

class LobbyWatcher : public Watcher
{
public:
    LobbyWatcher();

    static LobbyWatcher& instance();

    QString message();

protected:
    void watchAllGames();
    void watchGame(Game& game);
    void updateLobby();

    static QJsonObject toJson(int gameId);
    static QJsonArray toArray(const std::map<QString, Player>& players);
    static QString answer(const QJsonArray& games);
};
