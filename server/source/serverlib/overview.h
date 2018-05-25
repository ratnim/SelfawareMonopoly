#pragma once

#include <route.h>

class Overview : public Route
{
public:
    Overview();
    void mount(QWebSocket* socket, const Request& request) override;

protected:
    QString handle(const QJsonObject& message);

    QString createSession();
    QString createAnswer(const QString& userSession);
    bool createUser(const QString& name, const QString& session);

    QSqlQuery m_createUser;
};
