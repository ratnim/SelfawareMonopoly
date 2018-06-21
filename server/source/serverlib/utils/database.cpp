#include "database.h"

#include <QFile>
#include <QSqlError>
#include <QUuid>
#include <QVariant>

template <>
std::unique_ptr<Database> StaticStorage<Database>::s_model;

Database::Database(const QString& databaseName)
    : m_db(createDatabase(databaseName))
{
}

QSqlQuery Database::execute(const QString& queryString)
{
    QSqlQuery query = QSqlQuery(m_db);
    if (!query.exec(queryString))
    {
        throw std::runtime_error(query.lastError().text().toStdString());
    }

    return query;
}

QSqlQuery Database::prepare(const QString& queryString)
{
    QSqlQuery query = QSqlQuery(m_db);
    if (!query.prepare(queryString))
    {
        throw std::runtime_error(query.lastError().text().toStdString());
    }

    return query;
}

QSqlDatabase Database::createDatabase(const QString& databaseName)
{
    QFile::remove(databaseName);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid().toString());
    db.setDatabaseName(databaseName);
    db.open();

    return db;
}
