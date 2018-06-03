#pragma once

#include <QString>

class Exception
{
public:
    enum error
    {
        NoError = 0,
        InvalidRoute,
        UnsupportedAction,
        MalformedRequest,
        InvalidRequest,
        InternalError,
    };

    Exception(const QString& message, error code = InvalidRequest);

    QString json() const;

protected:
    const QString m_message;
    const error m_code;
};
