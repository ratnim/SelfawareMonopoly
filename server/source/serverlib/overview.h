#pragma once

#include <QSqlQuery>

#include <route.h>

class Overview : public Route
{
public:
    Overview();
    void mount(QWebSocket* socket) override;

    QString session(const QString& name);
    QString username(const QString& session);

protected:
    QString handle(const QJsonObject& message);

    QString createSession();
    QString createAnswer(const QString& userSession);
    bool createUser(const QString& name, const QString& session);

    static QString fetchFromDatabase(QSqlQuery& query);

    QSqlQuery m_sessionFromName;
    QSqlQuery m_nameFromSession;
    QSqlQuery m_createUser;
};
