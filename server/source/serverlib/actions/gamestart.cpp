#include "gamestart.h"

#include <QJsonDocument>
#include <QJsonObject>

GameStart::GameStart(const QString& playerName, Game& game)
    : GameAction(playerName, game)
{
    connect(&game, &Game::onGameStart, this, &GameStart::gameStart);
}

void GameStart::handle(const QJsonValue& body)
{
    m_game.start();
}

void GameStart::gameStart()
{
    emit send(answer());
}

QString GameStart::answer()
{
    QJsonObject answer({ { "name", "player_ready" } });
    return QJsonDocument(answer).toJson();
}
