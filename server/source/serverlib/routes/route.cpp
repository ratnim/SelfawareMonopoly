#include "route.h"

#include <QJsonDocument>

#include <utils/exception.h>

Route::Route(QWebSocket* socket)
    : QObject(socket)
    , m_socket(socket)
{
    connect(socket, &QWebSocket::textMessageReceived, this, &Route::incommingMessage);
    connect(socket, &QWebSocket::readChannelFinished, this, &Route::disconnectClient);
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
        m_socket->sendTextMessage(e.json());
    }
}

void Route::disconnectClient()
{
    m_socket->flush();
    m_socket->close();
    m_socket->deleteLater();
}

QJsonObject Route::toJson(const QString& message)
{
    const auto json = QJsonDocument::fromJson(message.toLatin1());
    if (json.isObject())
    {
        return json.object();
    }

    throw Exception("Malformed Request: Only JSON objects are supported", Exception::MalformedRequest);
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
