#pragma once

#include <connections/connection.h>

class LobbyConnection : public Connection
{
public:
    LobbyConnection(QWebSocket* parent, const ConnectionRequest& request);

protected:
    void watchLobby();
    
    void createGame(const QJsonValue& body);
    static QString createGameAnswer(int gameId);

    const QString m_playerName;
};
