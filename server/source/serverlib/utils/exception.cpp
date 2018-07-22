#include "exception.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaEnum>

Exception::Exception(const QString& message, error code)
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

QString Exception::errorString(error code)
{
    const auto conversion = QMetaEnum::fromType<error>();
    return QString(conversion.valueToKey(code));
}
