#pragma once

#include <QObject>
#include <QString>

class ErrorStringConverter : QObject
{
    Q_OBJECT
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
    Q_ENUM(error)
};

using error = ErrorStringConverter::error;

class Exception
{
public:
    Exception(const QString& message, error code = error::InvalidRequest);

    QString json() const;

protected:
    static QString errorString(error code);

    const QString m_message;
    const error m_code;
};
