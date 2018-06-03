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

/*
QJsonObject LobbyRoute::handleJoin(const QJsonValue& data, const QString& playerName)
{
    if (!data.isObject())
    {
        const auto error = QString("Invalid request: 'data' has to be an object");
        return generateError(error, InvalidRequest);
    }

    const auto dataObj = data.toObject();

    if (!dataObj.contains("game_id"))
    {
        const auto error = QString("Invalid request: 'data.game_id' required");
        return generateError(error, InvalidRequest);
    }

    const auto idVal = dataObj["game_id"];

    if (!idVal.isDouble())
    {
        const auto error = QString("Invalid request: 'data.game_id' has to be a number");
        return generateError(error, InvalidRequest);
    }

    const int GameRouteID = idVal.toInt(-1);

    if (GameRouteID == -1)
    {
        const auto error = QString("Invalid request: 'data.game_id' has to be a whole number");
        return generateError(error, InvalidRequest);
    }

    auto GameRoute = getGameRoute(GameRouteID);

    if (!GameRoute)
    {
        const auto error = QString("Internal Error: a GameRoute with id %1 does not exist").arg(GameRouteID);
        return generateError(error, InternalError);
    }

    if (!(GameRoute->currentPlayer == -1))
    {
        const auto error = QString("Internal Error: the GameRoute %1 already started").arg(GameRouteID);
        return generateError(error, InternalError);
    }

    if (std::any_of(GameRoute->players.begin(), GameRoute->players.end(), [&playerName](const PlayerState& state) { return state.name == playerName; }))
    {
        const auto error = QString("Internal Error: the player already joined the GameRoute").arg(GameRouteID);
        return generateError(error, InternalError);
    }

    GameRoute->players.push_back(PlayerState(playerName));

    return answer("join_GameRoute", GameRouteID);
}
*/