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
        const auto actionName = json[QString("request")].toString();

        const auto handler = actionHandler(actionName);
        handler(json[QString("data")]);
    }
    catch (const Exception &e)
    {
        emit send(e.json());
    }
}

QJsonObject Route::toJson(const QString& message)
{
    const auto json = QJsonDocument::fromJson(message.toUtf8());
    if (json.isObject())
    {
        return json.object();
    }

    throw Exception("Only JSON objects are supported.", error::MalformedRequest);
}

Route::ActionCallback Route::actionHandler(const QString& name) const
{
    const auto& action = m_actions.find(name);
    if (action == m_actions.end())
    {
        throw Exception(QString("'%1' is not valid.").arg(name), error::UnsupportedAction);
    }
    return action->second;
}
