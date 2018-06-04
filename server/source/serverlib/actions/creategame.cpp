#include "creategame.h"

#include <QJsonDocument>
#include <QJsonObject>

#include <models/gamemodel.h>

CreateGame::CreateGame(const QString& playerName)
    : m_playerName(playerName)
{
}

void CreateGame::handle(const QJsonValue& body)
{
    const auto gameId = GameModel::instance().createGame();
    emit send(answer(gameId));
}

QString CreateGame::answer(int gameId)
{
    QJsonObject answer({ { "name", "create_game" } });
    answer["data"] = QJsonObject({ { "game_id", gameId } });

    return QJsonDocument(answer).toJson();
}
