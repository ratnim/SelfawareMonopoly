#include "exception.h"

#include <QJsonDocument>
#include <QJsonObject>

Exception::Exception(const QString& message, error code)
    : m_message(message)
    , m_code(code)
{
}

QString Exception::json() const
{
    QJsonObject error;
    error["id"] = m_code;
    error["message"] = m_message;

    QJsonObject answer({{"error", error}});
    return QJsonDocument(answer).toJson();
}
