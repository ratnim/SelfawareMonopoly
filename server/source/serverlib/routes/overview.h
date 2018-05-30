#pragma once

#include <QSqlQuery>

#include <models/accountmodel.h>
#include <routes/route.h>

class Overview : public Route
{
public:
    Overview(QWebSocket* socket, const Request& request);

    void connectClient(QWebSocket* socket, const Request& request) override;

protected:
    QJsonObject handle(const QJsonObject& message);
    QJsonObject answer(const QString& userSession);

    AccountModel& m_state;
};
