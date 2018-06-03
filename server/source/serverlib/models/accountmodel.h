#pragma once

#include <map>

#include <QSqlQuery>
#include <QString>

class AccountModel
{
public:
    AccountModel();

    QString username(const QString& session);
    QString createUser(const QString& name);
    QString createSession(const QString& name);

    static AccountModel& instance();

protected:
    QSqlQuery s_createTable;
    QSqlQuery s_createUser;

    std::map<QString, QString> s_sessions;
};
