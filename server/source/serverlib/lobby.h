#pragma once

#include <route.h>

class Lobby : public Route
{
public:
    void mount(QWebSocket* socket, const Request& request) override;

protected:
    void unmount(QWebSocket* socket);

    void resendGameList();

    QString handle(const QJsonObject& message, const QString& playerName);
    QString handleCreate(const QString& playerName);
    QString handleJoin(const QJsonValue& data, const QString& playerName);
    QString answer(const QString& request, const int gameID);

protected:
    std::vector<QWebSocket*> m_gameListReceivers;
};
