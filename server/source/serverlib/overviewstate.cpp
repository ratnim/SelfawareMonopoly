#include "overviewstate.h"

#include <QVariant>

OverviewState::OverviewState(Database& db)
    : m_sessionFromName(db.prepare("SELECT session FROM accounts WHERE name=:player_name"))
    , m_nameFromSession(db.prepare("SELECT name FROM accounts WHERE session=:session"))
    , m_createUser(db.prepare("INSERT INTO accounts (name, session) VALUES (:name, :session)"))
{
}

QString OverviewState::session(const QString& name)
{
    m_sessionFromName.bindValue(":player_name", name);
    return fetchFromDatabase(m_sessionFromName);
}

QString OverviewState::username(const QString& session)
{
    m_nameFromSession.bindValue(":session", session);
    return fetchFromDatabase(m_nameFromSession);
}

bool OverviewState::createUser(const QString& name, const QString& session)
{
    m_createUser.bindValue(":name", name);
    m_createUser.bindValue(":session", session);
    return m_createUser.exec();
}

QString OverviewState::fetchFromDatabase(QSqlQuery& query)
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