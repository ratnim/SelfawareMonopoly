#pragma once
#include <QJsonObject>
#include <QWebSocket>
#include <QSqlQuery>

#include <request.h>

class Route : public QObject
{
public:
    Route();

    virtual void mount(QWebSocket* socket, const Request& request) = 0;

    enum error
    {
        InvalidRoute,
        UnsupportedAction,
        InvalidRequest,
        UserError,
        InternalError,
    };
    static QString generateError(const QString& message, error code);

protected:
    static void unmount(QWebSocket* socket);
    static QJsonObject toJson(const QString& message);

    QString session(const QString& name);
    QString username(const QString& session);

    static QString fetchFromDatabase(QSqlQuery& query);

protected:
    QSqlQuery m_sessionFromName;
    QSqlQuery m_nameFromSession;
};
