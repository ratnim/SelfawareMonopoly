#pragma once

#include <routes/playercommunication.h>

class Overview : public PlayerCommunication
{
public:
    Overview(QWebSocket* socket, const Request& request);

protected:
    QJsonObject handle(const QJsonObject& message);
    QJsonObject answer(const QString& userSession);
};
