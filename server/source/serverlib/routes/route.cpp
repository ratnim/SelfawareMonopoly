#include "route.h"

#include <QJsonDocument>

#include <utils/exception.h>

Route::Route(QWebSocket* parent)
    : Watcher(parent)
{
    connect(this, &Watcher::send, parent, &QWebSocket::sendTextMessage);
}

void Route::incommingMessage(const QString& message)
{
    try
    {
        const auto json = toJson(message);
        const auto actionName = json["request"].toString();

        const auto handler = actionHandler(actionName);
        handler(json["data"]);
    }
    catch (const Exception &e)
    {
        emit send(e.json());
    }
}

QJsonObject Route::toJson(const QString& message)
{
    const auto json = QJsonDocument::fromJson(message.toLatin1());
    if (json.isObject())
    {
        return json.object();
    }

    throw Exception("Malformed Request: Only JSON objects are supported.", Exception::MalformedRequest);
}

Route::ActionCallback Route::actionHandler(const QString& name) const
{
    auto& action = m_actions.find(name);
    if (action == m_actions.end())
    {
        throw Exception(QString("Unsupported Action: '%1'.").arg(name), Exception::UnsupportedAction);
    }
    return action->second;
}
