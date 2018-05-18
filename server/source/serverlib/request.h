#pragma once

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

struct Request
{
    enum Type
    {
        GET,
        POST,
        INVALID
    };

    Request(Type type = INVALID, const QString& path = QString(), const QJsonObject& body = QJsonObject());

    static QString extractPath(const QString& data);

    static Request fromString(const QString& data);
    static QJsonObject extractBody(const QString& data);

    static QByteArray toHttpAnswer(const QString& data);
    static QByteArray toJsonError(const QString& message);
    static QByteArray generateHttpError(int code);

    const Type type;
    const QString path;
    const QJsonObject body;
};
