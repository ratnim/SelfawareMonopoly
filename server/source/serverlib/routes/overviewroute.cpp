#include "overviewroute.h"

#include <QJsonDocument>
#include <QJsonObject>

#include <models/accountmodel.h>
#include <utils/exception.h>

OverviewRoute::OverviewRoute(QObject* parent, const Request& request)
    : Route(parent)
{
    m_actions["enter_lobby"] = [this](const QJsonValue& data) {
        enterLobby(data);
    };
}

void OverviewRoute::enterLobby(const QJsonValue& data)
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

    emit send(enterLobbyAnswer(userSession));
}

QString OverviewRoute::enterLobbyAnswer(const QString& userSession)
{
    QJsonObject answer({ { "name", "enter_lobby" } });
    answer["data"] = QJsonObject({ { "session", userSession } });

    return QJsonDocument(answer).toJson();
}
