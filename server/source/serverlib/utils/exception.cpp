#include "exception.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaEnum>

Exception::Exception(const QString& message, Error code)
    : m_message(message)
    , m_code(code)
{
}

QString Exception::json() const
{
    QJsonObject answer({ { "name", "error" } });

    QJsonObject error;
    error["id"] = static_cast<int>(m_code);
    error["message"] = errorString(m_code) + ": " + m_message;

    answer["data"] = error;
    return QJsonDocument(answer).toJson();
}

QString Exception::errorString(Error code)
{
    const auto conversion = QMetaEnum::fromType<Error>();
    return QString(conversion.valueToKey(code));
}
