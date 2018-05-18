#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

class Database
{
public:
    static QSqlQuery execute(const QString &queryString);
    static QSqlQuery prepare(const QString &queryString);
    static QSqlDatabase database();

protected:
    static QSqlDatabase createDatabase();
};
