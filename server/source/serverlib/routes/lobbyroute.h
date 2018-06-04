#pragma once

#include <actions/creategame.h>
#include <routes/route.h>

class LobbyRoute : public Route
{
public:
    LobbyRoute(QWebSocket* socket, const Request& request);

protected:
    const QString m_playerName;
    CreateGame m_createGame;
};
