#include "joingame.h"

#include <QJsonDocument>
#include <QJsonObject>

JoinGame::JoinGame(const QString& playerName, Game& game)
    : GameAction(playerName, game)
{
    connect(&game, &Game::onPlayerJoin, this, &JoinGame::playerJoin);
}

void JoinGame::handle(const QJsonValue& body)
{
    m_game.join(m_playerName);
}

void JoinGame::playerJoin(const QString& playerName)
{
    emit send(answer(playerName));
}

QString JoinGame::answer(const QString& playerName)
{
    QJsonObject answer({ { "name", "join_game" } });
    answer["data"] = playerName;

    return QJsonDocument(answer).toJson();
}
