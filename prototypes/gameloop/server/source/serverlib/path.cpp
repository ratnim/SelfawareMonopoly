#include "path.h"

Path::Path(Request::Type type, const QString& path, const std::function<QString(const Request&)>& callback)
    : m_type(type)
    , m_path(path)
    , m_callback(callback)
{
}

QString Path::match(const Request& request)
{
    if (request.m_type == m_type && request.m_path == m_path)
    {
        return m_callback(request);
    }
    return QString();
}