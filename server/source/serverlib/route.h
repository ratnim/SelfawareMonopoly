#pragma once
#include <QJsonObject>
#include <QWebSocket>
#include <QSqlQuery>

#include <request.h>

class Route : public QObject
{
public:
    Route();

    virtual void connectClient(QWebSocket* socket, const Request& request) = 0;

    enum error
    {
        NoError = 0,
        InvalidRoute,
        UnsupportedAction,
        MalformedRequest,
        InvalidRequest,
        InternalError,
    };
    static QJsonObject generateError(const QString& message, error code);

    static QJsonObject toJson(const QString& message);
    static QString toString(const QJsonObject& answer);

protected:
    static void disconnectClient(QWebSocket* socket);
};
