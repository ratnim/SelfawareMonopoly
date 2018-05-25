#pragma once

#include <map>

#include <QSqlQuery>

#include <database.h>

class AccountModel
{
public:
    AccountModel();

    QString username(const QString& session);
    QString createUser(const QString& name);
    QString createSession(const QString& name);

protected:
    QSqlQuery m_createTable;
    QSqlQuery m_createUser;

    std::map<QString, QString> m_sessions;
};
