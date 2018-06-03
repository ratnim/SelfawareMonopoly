#include "playerready.h"

#include <QJsonDocument>
#include <QJsonObject>

PlayerReady::PlayerReady(const QString& playerName, Game& game)
    : GameAction(playerName, game)
{
    connect(&game, &Game::onPlayerReady, this, &PlayerReady::playerReady);
}

void PlayerReady::handle(const QJsonValue& body)
{
    m_game.ready(m_playerName);
}

void PlayerReady::playerReady(const QString& playerName)
{
    emit send(answer(playerName));
}

QString PlayerReady::answer(const QString& playerName)
{
    QJsonObject answer({ { "name", "player_ready" } });
    answer["data"] = playerName;

    return QJsonDocument(answer).toJson();
}
