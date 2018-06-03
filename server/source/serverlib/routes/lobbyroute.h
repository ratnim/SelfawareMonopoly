#pragma once

#include <actions/lobbywatcher.h>
#include <models/accountmodel.h>
#include <routes/route.h>

class LobbyRoute : public Route
{
public:
    LobbyRoute(QWebSocket* socket, const Request& request);

protected:
    const QString m_playerName;
    LobbyWatcher m_watcher;
};
