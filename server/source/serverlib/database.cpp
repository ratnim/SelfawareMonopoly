#include "database.h"

#include <QDebug>
#include <QFile>
#include <QSqlError>
#include <QVariant>

namespace
{
static const QString dbName("monopoly.db3");
}

QSqlQuery Database::execute(const QString& queryString)
{
    QSqlQuery query = QSqlQuery(database());
    if (!query.exec(queryString))
    {
        throw std::runtime_error(query.lastError().text().toStdString());
    }

    return query;
}

QSqlQuery Database::prepare(const QString& queryString)
{
    QSqlQuery query = QSqlQuery(database());
    if (!query.prepare(queryString))
    {
        throw std::runtime_error(query.lastError().text().toStdString());
    }

    return query;
}

QSqlDatabase Database::database()
{
    static QSqlDatabase db = createDatabase();
    return db;
}

QSqlDatabase Database::createDatabase()
{
    QFile::remove(dbName);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    db.open();

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS accounts(name TEXT, session TEXT)");

    return db;
}
