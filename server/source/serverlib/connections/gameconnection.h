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
	void broadcastFiltered(const QString& player, const QString& message);

    const QString m_playerName;
};
