#pragma once

#include <QSqlQuery>

#include <overviewstate.h>
#include <route.h>

class Overview : public Route
{
public:
    Overview(OverviewState& overviewState);

    void mount(QWebSocket* socket, const Request& request) override;

protected:
    QJsonObject handle(const QJsonObject& message);

    QString session();
    QJsonObject answer(const QString& userSession);

    OverviewState& m_state;
};
