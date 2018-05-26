#include "accountmodel.h"

#include <QUuid>
#include <QVariant>

#include <utils/database.h>

AccountModel::AccountModel()
    : m_createTable(Database::execute("CREATE TABLE IF NOT EXISTS accounts(name TEXT UNIQUE NOT NULL)"))
    , m_createUser(Database::prepare("INSERT INTO accounts (name) VALUES (:name)"))
{
}

QString AccountModel::username(const QString& session)
{
    if (m_sessions.count(session))
    {
        return m_sessions[session];
    }
    return QString();
}

QString AccountModel::createUser(const QString& name)
{
    m_createUser.bindValue(":name", name);
    if (!m_createUser.exec())
    {
        return QString();
    }

    return createSession(name);
}

QString AccountModel::createSession(const QString& name)
{
    const auto session = QUuid::createUuid().toString();
    m_sessions[session] = name;

    return session;
}
