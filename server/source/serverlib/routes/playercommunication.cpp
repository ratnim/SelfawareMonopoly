#include "playercommunication.h"

#include <QJsonDocument>

#include <utils/database.h>

PlayerCommunication::PlayerCommunication(QWebSocket* socket)
    : QObject(socket)
    , m_socket(socket)
{
    connect(socket, &QWebSocket::textMessageReceived, this, &PlayerCommunication::incommingMessage);
    connect(socket, &QWebSocket::readChannelFinished, this, &PlayerCommunication::disconnectClient);
}

void PlayerCommunication::incommingMessage(const QString& message)
{
    // TODO CATCH EXCEPTIONS HERE

    const auto json = toJson(message);
    const auto action = json["request"];

    // GET DATA packet and carry on

    const auto answer = handle();
    m_socket->sendTextMessage(toString(answer));
}

void PlayerCommunication::disconnectClient()
{
    m_socket->flush();
    m_socket->close();
    m_socket->deleteLater();
}

QJsonObject PlayerCommunication::toJson(const QString& message)
{
    const auto json = QJsonDocument::fromJson(message.toLatin1());
    if (json.isObject())
    {
        return json.object();
    }

    qWarning().noquote() << "Only JSON objects are supported.";
    return QJsonObject();
}

QString PlayerCommunication::toString(const QJsonObject& answer)
{
    return QJsonDocument(answer).toJson();
}

QJsonObject PlayerCommunication::generateError(const QString& message, error code)
{
    QJsonObject answer;
    {
        QJsonObject error;
        error["id"] = code;
        error["message"] = message;

        answer["error"] = error;
    }
    return answer;
}
