#include "accountmodel.h"

#include <QUuid>
#include <QVariant>

#include <utils/database.h>
#include <utils/exception.h>

template<>
std::unique_ptr<AccountModel> StaticStorage<AccountModel>::s_model;

AccountModel::AccountModel()
{
    m_createTable = Database::instance().execute("CREATE TABLE IF NOT EXISTS accounts(name TEXT UNIQUE NOT NULL)");
    m_createUser = Database::instance().prepare("INSERT INTO accounts (name) VALUES (:name)");
}

QString AccountModel::username(const QString& session)
{
    if (m_sessions.count(session))
    {
        return m_sessions[session];
    }
    throw Exception("Session is not valid.");
}

QString AccountModel::createUser(const QString& name)
{
    m_createUser.bindValue(":name", name);
    if (!m_createUser.exec())
    {
        throw Exception("Could not create user account. The player name is probably already taken.");
    }

    return createSession(name);
}

QString AccountModel::createSession(const QString& name)
{
    const auto session = QUuid::createUuid().toString();
    m_sessions[session] = name;

    return session;
}
