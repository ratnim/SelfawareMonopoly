#pragma once

#include "request.h"

#include <map>

class FileServer
{
public:
    static QByteArray handle(const Request request);

protected:
    static std::map<QString, QString> createRoutes();
    static QByteArray staticPage(const QString& filename);
};