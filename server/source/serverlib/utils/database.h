#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

#include <utils/staticstorage.h>

class Database : public StaticStorage<Database>
{
public:
    Database(const QString& databaseName = ":memory:");

    QSqlQuery execute(const QString& queryString);
    QSqlQuery prepare(const QString& queryString);

protected:
    static QSqlDatabase createDatabase(const QString& databaseName);

    QSqlDatabase m_db;
};
