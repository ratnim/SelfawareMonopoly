#pragma once

#include <game/game.h>
#include <routes/route.h>

class GameRoute : public Route
{
public:
    GameRoute(QObject* parent, const Request& request);

    void watchGame(GameWatcher& watcher);

protected:
    const QString m_playerName;
};
