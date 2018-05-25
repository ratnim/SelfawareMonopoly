#pragma once

#include <overviewstate.h>
#include <route.h>

class Lobby : public Route
{
public:
    Lobby(OverviewState& overviewState);

    void connectClient(QWebSocket* socket, const Request& request) override;

protected:
    void disconnectClient(QWebSocket* socket);

    QJsonObject handle(const QJsonObject& message, const QString& playerName);
    QJsonObject handleCreate(const QString& playerName);
    QJsonObject handleJoin(const QJsonValue& data, const QString& playerName);
    QJsonObject answer(const QString& request, const int gameID);

protected:
    OverviewState& m_overviewState;
    std::vector<QWebSocket*> m_gameListReceivers;
};
