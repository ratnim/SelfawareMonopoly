#pragma once

#include <functional>

#include "request.h"

class Path
{
public:
    Path(Request::Type type, const QString& path, const std::function<QString(const Request&)>& callback);

    QString match(const Request& request);

protected:
    const Request::Type m_type;
    const QString m_path;
    const std::function<QString(const Request&)> m_callback;
};
