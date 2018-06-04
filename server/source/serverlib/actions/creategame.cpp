#include "creategame.h"

#include <QJsonDocument>
#include <QJsonObject>

#include <models/gamemodel.h>
#include <utils/exception.h>

CreateGame::CreateGame(const QString& playerName)
    : m_playerName(playerName)
{
}

void CreateGame::handle(const QJsonValue& body)
{
    const auto label = body["game_label"].toString();
    if (label.isEmpty())
    {
        throw Exception("Malformed Request: data.game_label is missing.");
    }

    const auto gameId = GameModel::instance().createGame(label);
    emit send(answer(gameId));
}

QString CreateGame::answer(int gameId)
{
    QJsonObject answer({ { "name", "create_game" } });
    answer["data"] = QJsonObject({ { "game_id", gameId } });

    return QJsonDocument(answer).toJson();
}
