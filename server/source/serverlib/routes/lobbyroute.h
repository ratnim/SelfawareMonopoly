#pragma once

#include <routes/route.h>

class LobbyRoute : public Route
{
public:
    LobbyRoute(QWebSocket* socket, const Request& request);

protected:
    void createGame(QWebSocket* socket, const QJsonValue& body);
    static QString createGameAnswer(int gameId);

    const QString m_playerName;
};
