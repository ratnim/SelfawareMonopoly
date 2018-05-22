#pragma once
#include <QJsonObject>
#include <QWebSocket>

class Route : public QObject
{
public:
    virtual void mount(QWebSocket* socket) = 0;

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
    virtual void unmount(QWebSocket* socket);
    static QJsonObject toJson(const QString& message);
};
