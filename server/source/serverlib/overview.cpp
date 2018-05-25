#include "overview.h"

#include <QJsonDocument>
#include <QSqlQuery>
#include <QUuid>

#include <database.h>

Overview::Overview()
    : Route()
    , m_createUser(Database::prepare("INSERT INTO accounts (name, session) VALUES (:name, :session)"))
{
}

void Overview::mount(QWebSocket* socket, const Request& /*request*/)
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

    if (!session(player).isEmpty())
    {
        const auto error = QString("User error: There is already a player with the name '%1'.").arg(player);
        return generateError(error, UserError);
    }

    const auto userSession = createSession();
    if (!createUser(player, userSession))
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
    } while (!username(userSession).isEmpty());

    return userSession;
}

bool Overview::createUser(const QString& name, const QString& session)
{
    m_createUser.bindValue(":name", name);
    m_createUser.bindValue(":session", session);
    return m_createUser.exec();
}

QString Overview::createAnswer(const QString& userSession)
{
    QJsonObject answer;
    answer["name"] = "enter_lobby";
    answer["data"] = QJsonObject({ { "session", userSession } });
    return QJsonDocument(answer).toJson();
}

