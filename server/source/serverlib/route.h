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
    static QJsonObject generateError(const QString& message, error code);

    static QJsonObject toJson(const QString& message);
    static QString toString(const QJsonObject& answer);

protected:
    static void unmount(QWebSocket* socket);
};
