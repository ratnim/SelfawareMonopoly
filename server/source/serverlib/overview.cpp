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
        socket->sendTextMessage(answer);
    });

    connect(socket, &QWebSocket::readChannelFinished, this, [this, socket] {
        unmount(socket);
    });
}

QString Overview::handle(const QJsonObject& message)
{
    if (message["request"] != "enter_lobby")
    {
        const auto error = QString("Unsupported action: '%1'.").arg(message["request"].toString());
        return generateError(error, UnsupportedAction);
    }

    const auto data = message["data"];
    if (!data.isObject())
    {
        const auto error = QString("Invalid request: Data is not a JSON object.");
        return generateError(error, InvalidRequest);
    }

    auto dataObject = data.toObject();
    const auto player = dataObject["player_name"].toString();
    if (player.isEmpty())
    {
        const auto error = QString("Invalid request: 'player_name' is missing.");
        return generateError(error, InvalidRequest);
    }

    if (!m_state.session(player).isEmpty())
    {
        const auto error = QString("User error: There is already a player with the name '%1'.").arg(player);
        return generateError(error, UserError);
    }

    const auto userSession = createSession();
    if (!m_state.createUser(player, userSession))
    {
        const auto error = QString("Internal error: Could not create user account.");
        return generateError(error, InternalError);
    }

    return createAnswer(userSession);
}

QString Overview::createSession()
{
    QString userSession;
    do
    {
        userSession = QUuid::createUuid().toString();
    } while (!m_state.username(userSession).isEmpty());

    return userSession;
}

QString Overview::createAnswer(const QString& userSession)
{
    QJsonObject answer;
    answer["name"] = "enter_lobby";
    answer["data"] = QJsonObject({ { "session", userSession } });
    return QJsonDocument(answer).toJson();
}
