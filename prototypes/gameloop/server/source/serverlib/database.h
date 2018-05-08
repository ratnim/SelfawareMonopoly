#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

class Database
{
public:
    Database();

    void send(const QString &message);

    QString receive();

protected:
    static QSqlDatabase createDatabase();
    QSqlQuery prepareSend();
    QSqlQuery prepareReceive();

    QSqlDatabase m_database;
    QSqlQuery m_send;
    QSqlQuery m_receive;
};
