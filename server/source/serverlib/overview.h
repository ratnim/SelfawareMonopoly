#pragma once

#include <QSqlQuery>

#include <accountmodel.h>
#include <route.h>

class Overview : public Route
{
public:
    Overview(AccountModel& overviewState);

    void connectClient(QWebSocket* socket, const Request& request) override;

protected:
    QJsonObject handle(const QJsonObject& message);
    QJsonObject answer(const QString& userSession);

    AccountModel& m_state;
};
