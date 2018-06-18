#include "overviewroute.h"

#include <QJsonDocument>
#include <QJsonObject>

#include <models/accountmodel.h>
#include <utils/exception.h>

OverviewRoute::OverviewRoute(QWebSocket* parent, const Request& request)
    : Route(parent)
{
    m_actions["enter_lobby"] = [this](const QJsonValue& data) {
        enterLobby(data);
    };
}

void OverviewRoute::enterLobby(const QJsonValue& data)
{
    const auto rawPlayer = data["player_name"].toString();
    const auto player = rawPlayer.simplified().toHtmlEscaped();
    if (player.isEmpty())
    {
        throw Exception("'data.player_name' is missing.", error::MalformedRequest);
    }

    static const int maxNameLength = 32;
    if (player.size() > maxNameLength)
    {
        throw Exception("The name is too long.");
    }

    const auto userSession = AccountModel::instance().createUser(player);
    emit send(enterLobbyAnswer(userSession));
}

QString OverviewRoute::enterLobbyAnswer(const QString& userSession)
{
    QJsonObject answer({ { "name", "enter_lobby" } });
    answer["data"] = QJsonObject({ { "session", userSession } });

    return QJsonDocument(answer).toJson();
}
