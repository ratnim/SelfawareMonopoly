#include "overview.h"

#include <QJsonDocument>
#include <QSqlQuery>
#include <QUuid>

#include <database.h>

Overview::Overview(OverviewState& overviewState)
    : m_state(overviewState)
{
}

void Overview::mount(QWebSocket* socket)
{
    connect(socket, &QWebSocket::textMessageReceived, [this, socket](const QString& message) {
        const auto answer = handle(toJson(message));
        socket->sendTextMessage(toString(answer));
    });

    connect(socket, &QWebSocket::readChannelFinished, this, [this, socket] {
        unmount(socket);
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
        const auto error = QString("Invalid request: 'data.player_name' is missing.");
        return generateError(error, InvalidRequest);
    }

    const auto userSession = session();
    if (!m_state.createUser(player, userSession))
    {
        const auto error = QString("User error: Could not create user account. The player name is probably already taken.");
        return generateError(error, UserError);
    }

    return answer(userSession);
}

QString Overview::session()
{
    return QUuid::createUuid().toString();
}

QJsonObject Overview::answer(const QString& userSession)
{
    QJsonObject answer;
    answer["name"] = "enter_lobby";
    answer["data"] = QJsonObject({ { "session", userSession } });
    return answer;
}
