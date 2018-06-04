#include "overviewroute.h"

#include <QJsonDocument>
#include <QJsonObject>

#include <models/accountmodel.h>
#include <utils/exception.h>

OverviewRoute::OverviewRoute(QWebSocket* socket, const Request& request)
    : Route(socket)
{
    m_actions["enter_lobby"] = [this, socket](const QJsonValue& data) {
        enterLobby(socket, data);
    };
}

void OverviewRoute::enterLobby(QWebSocket* socket, const QJsonValue& data)
{
    const auto player = data["player_name"].toString();
    if (player.isEmpty())
    {
        throw Exception("Malformed request: 'data.player_name' is missing.", Exception::MalformedRequest);
    }

    const auto userSession = AccountModel::instance().createUser(player);
    if (userSession.isEmpty())
    {
        throw Exception("Internal error: Could not create session.", Exception::InternalError);
    }

    socket->sendTextMessage(enterLobbyAnswer(userSession));
}

QString OverviewRoute::enterLobbyAnswer(const QString& userSession)
{
    QJsonObject answer({ { "name", "enter_lobby" } });
    answer["data"] = QJsonObject({ { "session", userSession } });

    return QJsonDocument(answer).toJson();
}
