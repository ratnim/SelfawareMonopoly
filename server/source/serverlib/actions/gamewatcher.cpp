#include "gamewatcher.h"

#include <QJsonDocument>

#include <models/gamemodel.h>

GameWatcher::GameWatcher(const Game& game)
    : m_game(game)
{
    connect(&game, &Game::onPlayerMove, this, &GameWatcher::playerMove);
    connect(&game, &Game::onGameEnd, this, &GameWatcher::gameEnd);
}

void GameWatcher::playerMove(int distance)
{
    emit send(moveAnswer(distance));
}

void GameWatcher::gameEnd()
{
    emit send(gameEndAnswer());
}

QString GameWatcher::moveAnswer(int distance)
{
    QJsonObject answer({ { "name", "player_move" } });
    answer["data"] = distance;

    return QJsonDocument(answer).toJson();
}

QString GameWatcher::gameEndAnswer()
{
    QJsonObject answer({ { "name", "end_game" } });
    return QJsonDocument(answer).toJson();
}
