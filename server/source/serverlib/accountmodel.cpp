#include "accountmodel.h"

#include <QVariant>

AccountModel::AccountModel()
    : m_createTable(Database::execute("CREATE TABLE IF NOT EXISTS accounts(id INTEGER PRIMARY KEY, name TEXT UNIQUE NOT NULL, session TEXT UNIQUE NOT NULL)"))
    , m_sessionFromName(Database::prepare("SELECT session FROM accounts WHERE name=:player_name"))
    , m_nameFromSession(Database::prepare("SELECT name FROM accounts WHERE session=:session"))
    , m_createUser(Database::prepare("INSERT INTO accounts (name, session) VALUES (:name, :session)"))
{
}

QString AccountModel::session(const QString& name)
{
    m_sessionFromName.bindValue(":player_name", name);
    return fetchFromDatabase(m_sessionFromName);
}

QString AccountModel::username(const QString& session)
{
    m_nameFromSession.bindValue(":session", session);
    return fetchFromDatabase(m_nameFromSession);
}

bool AccountModel::createUser(const QString& name, const QString& session)
{
    m_createUser.bindValue(":name", name);
    m_createUser.bindValue(":session", session);
    return m_createUser.exec();
}

QString AccountModel::fetchFromDatabase(QSqlQuery& query)
{
    auto result = query.exec();
    if (!result)
    {
        throw std::runtime_error("Session query failed.");
    }

    if (query.next())
    {
        return query.value(0).toString();
    }
    return QString();
}
