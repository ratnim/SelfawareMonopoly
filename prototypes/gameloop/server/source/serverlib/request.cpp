#include "request.h"

#include <QByteArray>
#include <QDebug>
#include <QStringList>

QString Request::extractPath(const QString& data)
{
    const auto request = data.split("\r\n");
    auto request_header = request[0].split(' ');
    if (request_header.size() == 3)
    {
        return request_header[1];
    }
    
    qWarning() << "Invalid request header.";
    return QString();
}

QByteArray Request::toHttpRequest(const QByteArray& data)
{
    QByteArray request;
    request += QString("HTTP/1.1 200 OK\r\n");
    request += QString("Content-Length : %1\r\n").arg(data.size());
    request += QString("Connection : close\r\n\r\n");
    request += data;

    return request;
}
