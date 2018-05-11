#include "request.h"

#include <QByteArray>
#include <QDebug>
#include <QStringList>
#include <QUrl>

Request::Request(Type type, const QString& path, const QString& body)
    : m_type(type)
    , m_path(path)
    , m_body(body)
{
}

Request Request::fromString(const QString& data)
{
    const auto request = data.split("\r\n");
    auto request_header = request[0].split(' ');
    if (request_header.size() == 3)
    {
        if (request_header[0] == "GET")
        {
            return { GET, request_header[1] };
        }
        if (request_header[0] == "POST")
        {
            return { POST, request_header[1], extractBody(data) };
        }
    }
    
    qWarning() << "Invalid request header.";
    return Request();
}

QString Request::extractBody(const QString& data)
{
    const auto request = data.split("\r\n\r\n");
    if (request.size() == 2)
    {
        return request[1];
    }

    qWarning() << "Invalid request.";
    return QString();
}

QByteArray Request::toHttpRequest(const QString& data)
{
    QByteArray request;
    request += QString("HTTP/1.1 200 OK\r\n");
    request += QString("Content-Length : %1\r\n").arg(data.size());
    request += QString("Connection : close\r\n\r\n");
    request += data;

    return request;
}
