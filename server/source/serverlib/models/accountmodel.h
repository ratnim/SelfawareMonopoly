#pragma once

#include <map>

#include <QSqlQuery>
#include <QString>

#include <utils/staticstorage.h>

class AccountModel : public StaticStorage<AccountModel>
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
