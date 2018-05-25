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
    static QJsonObject generateError(const QString& message, error code);

    static QJsonObject toJson(const QString& message);
    static QString toString(const QJsonObject& answer);

protected:
    static void unmount(QWebSocket* socket);
};
