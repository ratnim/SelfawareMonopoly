#pragma once

#include <connections/connection.h>

class OverviewConnection : public Connection
{
public:
    OverviewConnection(QWebSocket* parent, const Request& request);

protected:
    void enterLobby(const QJsonValue& data);
    static QString enterLobbyAnswer(const QString& userSession);
};
