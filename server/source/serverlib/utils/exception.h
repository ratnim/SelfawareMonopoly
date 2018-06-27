#pragma once

#include <QObject>
#include <QString>

class ErrorStringConverter : QObject
{
    Q_OBJECT
public:
    enum Error
    {
        NoError = 0,
        InvalidRoute,
        UnsupportedAction,
        MalformedRequest,
        InvalidRequest,
        InternalError,
    };
    Q_ENUM(Error)
};

using Error = ErrorStringConverter::Error;

class Exception
{
public:
    Exception(const QString& message, Error code = Error::InvalidRequest);

    QString json() const;

protected:
    static QString errorString(error code);

    const QString m_message;
    const error m_code;
};
