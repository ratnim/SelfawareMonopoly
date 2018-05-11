#pragma once

#include <QByteArray>
#include <QJsonDocument>
#include <QString>

class Request
{
public:
    enum Type
    {
        GET,
        POST,
        INVALID
    };

    Request(Type type = INVALID, const QString& path = QString(), const QString& body = QString());

    static Request fromString(const QString& data);
    static QString extractBody(const QString& data);

    static QByteArray toHttpRequest(const QString& data);

//protected:
    const Type m_type;
    const QString m_path;
    const QString m_body;
};
