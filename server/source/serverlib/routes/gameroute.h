#pragma once

#include <game/game.h>
#include <watchers/gamewatcher.h>
#include <routes/route.h>

class GameRoute : public Route
{
public:
    GameRoute(QWebSocket* parent, const Request& request);

    void watchGame(GameWatcher& watcher);

protected:
    const QString m_playerName;
};
