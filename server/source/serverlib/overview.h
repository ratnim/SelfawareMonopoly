#pragma once

#include <QSqlQuery>

#include <overviewstate.h>
#include <route.h>

class Overview : public Route
{
public:
    Overview(OverviewState& overviewState);

    void mount(QWebSocket* socket) override;

protected:
    QString handle(const QJsonObject& message);

    QString createSession();
    QString createAnswer(const QString& userSession);

    OverviewState& m_state;
};
