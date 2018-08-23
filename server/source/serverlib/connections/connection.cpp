#include "connection.h"

#include <iostream>

#include <QJsonDocument>

#include <utils/exception.h>

Connection::Connection(QWebSocket* parent)
    : Watcher(parent)
{
    connect(this, &Watcher::broadcast, parent, &QWebSocket::sendTextMessage);
}

void Connection::incommingMessage(const QString& message)
{
    std::cout << "Recieved: " + message.toStdString() << std::endl;
    try
    {
        const auto json = toJson(message);
        const auto actionName = json[QString("request")].toString();

        const auto handler = requestHandler(actionName);
        handler(json[QString("data")]);
    }
    catch (const Exception &e)
    {
        std::cout << "Send: " + e.json().toStdString() << std::endl;
        emit broadcast(e.json());
    }
}

QJsonObject Connection::toJson(const QString& message)
{
    const auto json = QJsonDocument::fromJson(message.toUtf8());
    if (json.isObject())
    {
        return json.object();
    }

    throw Exception("Only JSON objects are supported.", Error::MalformedRequest);
}

Connection::RequestCallback Connection::requestHandler(const QString& name) const
{
    const auto& action = m_requests.find(name);
    if (action == m_requests.end())
    {
        throw Exception(QString("'%1' is not valid.").arg(name), Error::UnsupportedAction);
    }
    return action->second;
}
