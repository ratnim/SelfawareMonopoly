#include "overview.h"

#include <QJsonDocument>

Overview::Overview(QWebSocket* socket, const Request& request)
    : m_state(overviewState)
{
}

void Overview::connectClient(QWebSocket* socket, const Request& /*request*/)
{
    connect(socket, &QWebSocket::textMessageReceived, [this, socket](const QString& message) {
        const auto answer = handle(toJson(message));
        socket->sendTextMessage(toString(answer));
    });

    connect(socket, &QWebSocket::readChannelFinished, this, [this, socket] {
        disconnectClient(socket);
    });
}

QJsonObject Overview::handle(const QJsonObject& message)
{
    if (message["request"] != "enter_lobby")
    {
        const auto error = QString("Unsupported action: '%1'.").arg(message["request"].toString());
        return generateError(error, UnsupportedAction);
    }

    auto data = message["data"].toObject();
    const auto player = data["player_name"].toString();
    if (player.isEmpty())
    {
        const auto error = QString("Malformed request: 'data.player_name' is missing.");
        return generateError(error, MalformedRequest);
    }

    const auto userSession = m_state.createUser(player);
    if (userSession.isEmpty())
    {
        const auto error = QString("Invalid error: Could not create user account. The player name is probably already taken.");
        return generateError(error, InvalidRequest);
    }

    return answer(userSession);
}

QJsonObject Overview::answer(const QString& userSession)
{
    QJsonObject answer({ { "name", "enter_lobby" } });
    answer["data"] = QJsonObject({ { "session", userSession } });

    return answer;
}
