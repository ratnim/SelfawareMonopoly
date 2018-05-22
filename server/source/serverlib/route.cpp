#include "route.h"

#include <QJsonDocument>

void Route::unmount(QWebSocket* socket)
{
    socket->flush();
    socket->close();
    socket->deleteLater();
}

QJsonObject Route::toJson(const QString& message)
{
    const auto json = QJsonDocument::fromJson(message.toLatin1());
    if (json.isObject())
    {
        return json.object();
    }

    qWarning().noquote() << "Only JSON objects are supported.";
    return QJsonObject();
}

QString Route::generateError(const QString& message, error code)
{
    QJsonObject answer;
    {
        QJsonObject error;
        error["id"] = code;
        error["message"] = message;

        answer["error"] = error;
    }
    return QJsonDocument(answer).toJson();
}
