#pragma once

#include <game/game.h>
#include <watchers/gamewatcher.h>
#include <connections/connection.h>

class GameConnection : public Connection
{
public:
    GameConnection(QWebSocket* parent, const Request& request);

    void watchGame(GameWatcher& watcher);

protected:
    const QString m_playerName;
};
