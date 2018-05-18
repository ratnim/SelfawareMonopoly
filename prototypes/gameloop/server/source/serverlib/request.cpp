#include "request.h"

#include <QByteArray>
#include <QDebug>
#include <QStringList>
#include <QUrl>

Request::Request(Type type, const QString& path, const QJsonObject& body)
    : type(type)
    , path(path)
    , body(body)
{
}

Request Request::fromString(const QString& data)
{
    const auto request = data.split("\r\n");
    auto request_header = request[0].split(' ');
    if (request_header.size() == 3)
    {
        const auto url = request_header[1].split('?');
        if (request_header[0] == "GET")
        {
            return { GET, url[0] };
        }
        if (request_header[0] == "POST")
        {
            return { POST, url[0], extractBody(data) };
        }
    }
    
    qWarning().noquote() << "Invalid request header:" << data;
    return Request();
}

QJsonObject Request::extractBody(const QString& data)
{
    const auto request = data.split("\r\n\r\n");
    if (request.size() != 2)
    {
        qWarning().noquote() << "Invalid request:" << data;
        return QJsonObject();
    }

    const auto json = QJsonDocument::fromJson(request[1].toUtf8());
    if (!json.isObject())
    {
        qWarning().noquote() << "Only JSON objects are supported.";
        return QJsonObject();
    }

    return json.object();
}

QByteArray Request::toHttpAnswer(const QString& data)
{
    QByteArray request;
    request += QString("HTTP/1.1 200 OK\r\n");
    request += QString("Content-Length : %1\r\n").arg(data.size());
    request += QString("Connection : close\r\n\r\n");
    request += data;

    return request;
}

QByteArray Request::toJsonError(const QString& message)
{
    QJsonObject body({ { "error", message } });
    return QJsonDocument(body).toJson();
}

QByteArray Request::generateHttpError(int code)
{
    QByteArray request;
    request += QString("HTTP/1.1 %1 Not Found").arg(code);

    return request;
}
