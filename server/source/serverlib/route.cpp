#include "route.h"

#include <QJsonDocument>

#include <database.h>

Route::Route()
    : m_sessionFromName(Database::prepare("SELECT session FROM accounts WHERE name=:player_name"))
    , m_nameFromSession(Database::prepare("SELECT name FROM accounts WHERE session=:session"))
{
}

void Route::unmount(QWebSocket* socket)
{
    socket->flush();
    socket->close();
    socket->deleteLater();
}

QJsonObject Route::toJson(const QString& message)
{
    const auto json = QJsonDocument::fromJson(message.toLatin1());
    if (json.isObject())
    {
        return json.object();
    }

    qWarning().noquote() << "Only JSON objects are supported.";
    return QJsonObject();
}

QString Route::generateError(const QString& message, error code)
{
    QJsonObject answer;
    {
        QJsonObject error;
        error["id"] = code;
        error["message"] = message;

        answer["error"] = error;
    }
    return QJsonDocument(answer).toJson();
}

QString Route::session(const QString& name)
{
    m_sessionFromName.bindValue(":player_name", name);
    return fetchFromDatabase(m_sessionFromName);
}

QString Route::username(const QString& session)
{
    m_nameFromSession.bindValue(":session", session);
    return fetchFromDatabase(m_nameFromSession);
}

QString Route::fetchFromDatabase(QSqlQuery& query)
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
