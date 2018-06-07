#pragma once

#include <routes/route.h>

class LobbyRoute : public Route
{
public:
    LobbyRoute(QWebSocket* parent, const Request& request);

protected:
    void watchLobby();
    
    void createGame(const QJsonValue& body);
    static QString createGameAnswer(int gameId);

    const QString m_playerName;
};
