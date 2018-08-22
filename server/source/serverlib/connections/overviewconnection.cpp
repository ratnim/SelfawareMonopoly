#include "overviewconnection.h"

#include <QJsonDocument>
#include <QJsonObject>

#include <models/accountmodel.h>
#include <utils/exception.h>

OverviewConnection::OverviewConnection(QWebSocket* parent, const Request& request)
    : Connection(parent)
{
    m_actions[QString("enter_lobby")] = [this](const QJsonValue& data) {
        enterLobby(data);
    };
}

void OverviewConnection::enterLobby(const QJsonValue& data)
{
    const auto rawPlayer = data[QString("player_name")].toString();
    const auto player = rawPlayer.simplified().toHtmlEscaped();
    if (player.isEmpty())
    {
        throw Exception("'data.player_name' is missing.", Error::MalformedRequest);
    }

    static const int maxNameLength = 32;
    if (player.size() > maxNameLength)
    {
        throw Exception("The name is too long.");
    }

    const auto userSession = AccountModel::instance().createUser(player);
    emit broadcast(enterLobbyAnswer(userSession));
}

QString OverviewConnection::enterLobbyAnswer(const QString& userSession)
{
    QJsonObject answer({ { "name", "enter_lobby" } });
    answer[QString("data")] = QJsonObject({ { "session", userSession } });

    return QJsonDocument(answer).toJson();
}
