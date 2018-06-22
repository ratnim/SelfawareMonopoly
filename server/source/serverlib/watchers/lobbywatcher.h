#pragma once

#include <QJsonArray>
#include <QJsonObject>

#include <watchers/watcher.h>
#include <game/gameinfo.h>
#include <utils/staticstorage.h>

class LobbyWatcher : public StaticStorage<LobbyWatcher>, public Watcher
{
public:
    LobbyWatcher();

    static LobbyWatcher& instance();

    QString message();

protected:
    void watchAllGames();
    void watchGame(const GameInfo& info);
    void updateLobby();

    static QJsonObject toJson(int gameId);
    static QJsonArray toArray(const std::vector<QString>& players);
    static QString answer(const QJsonArray& games);
};
