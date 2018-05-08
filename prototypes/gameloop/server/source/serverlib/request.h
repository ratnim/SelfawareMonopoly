#pragma once

#include <QByteArray>
#include <QString>

class Request
{
public:
    static QString extractPath(const QString& data);
    static QByteArray toHttpRequest(const QByteArray& data);
};
