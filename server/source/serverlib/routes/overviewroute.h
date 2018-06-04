#pragma once

#include <routes/route.h>

class OverviewRoute : public Route
{
public:
    OverviewRoute(QWebSocket* socket, const Request& request);

protected:
    void enterLobby(QWebSocket* socket, const QJsonValue& data);
    static QString enterLobbyAnswer(const QString& userSession);
};
