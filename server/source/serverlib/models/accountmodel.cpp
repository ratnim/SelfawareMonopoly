#include "accountmodel.h"

#include <QUuid>
#include <QVariant>

#include <utils/database.h>
#include <utils/exception.h>

AccountModel::AccountModel()
{
    s_createTable = Database::execute("CREATE TABLE IF NOT EXISTS accounts(name TEXT UNIQUE NOT NULL)");
    s_createUser = Database::prepare("INSERT INTO accounts (name) VALUES (:name)");
}

QString AccountModel::username(const QString& session)
{
    if (s_sessions.count(session))
    {
        return s_sessions[session];
    }
    throw Exception("Invalid Request: Session is not valid.");
}

QString AccountModel::createUser(const QString& name)
{
    s_createUser.bindValue(":name", name);
    if (!s_createUser.exec())
    {
        throw Exception("Invalid request: Could not create user account. The player name is probably already taken.", Exception::InvalidRequest);
    }

    return createSession(name);
}

QString AccountModel::createSession(const QString& name)
{
    const auto session = QUuid::createUuid().toString();
    s_sessions[session] = name;

    return session;
}

AccountModel& AccountModel::instance()
{
    static AccountModel model;
    return model;
}