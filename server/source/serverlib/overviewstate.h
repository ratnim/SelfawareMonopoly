#pragma once

#include <QSqlQuery>

#include <database.h>

class OverviewState
{
public:
    OverviewState(Database& db);

    QString session(const QString& name);
    QString username(const QString& session);

    bool createUser(const QString& name, const QString& session);

protected:
    static QString fetchFromDatabase(QSqlQuery& query);

    QSqlQuery m_sessionFromName;
    QSqlQuery m_nameFromSession;
    QSqlQuery m_createUser;
};
