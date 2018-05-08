#include "database.h"

#include <QFile>
#include <QSqlError>
#include <QVariant>

namespace
{
static const QString dbName("myDatabase.db3");
}

Database::Database()
    : m_database(createDatabase())
    , m_send(prepareSend())
    , m_receive(prepareReceive())
{
}

QSqlQuery Database::prepareSend()
{
    QSqlQuery query = QSqlQuery(m_database);
    query.prepare("INSERT INTO messageTable (message) VALUES (:message)");

    return query;
}

void Database::send(const QString &message)
{
    m_send.bindValue(":message", message);
    if (!m_send.exec())
    {
        throw std::runtime_error(m_send.lastError().text().toStdString());
    }
}

QSqlQuery Database::prepareReceive()
{
    QSqlQuery query = QSqlQuery(m_database);
    query.prepare("SELECT message from messageTable");

    return query;
}

QString Database::receive()
{
    if (!m_receive.exec())
    {
        throw std::runtime_error(m_receive.lastError().text().toStdString());
    }
    if (m_receive.first())
    {
        return m_receive.value(0).toString();
    }
    else
    {
        return QString();
    }
}

QSqlDatabase Database::createDatabase()
{
    QFile::remove(dbName);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    db.open();

    QSqlQuery query = QSqlQuery(db);
    query.exec("CREATE TABLE IF NOT EXISTS messageTable ( message TEXT )");

    return db;
}
