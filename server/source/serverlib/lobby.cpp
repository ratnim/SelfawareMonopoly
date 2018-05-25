
#include "lobby.h"

#include <QJsonDocument>

#include <gamestate.h>

void Lobby::mount(QWebSocket* socket, const Request& request)
{
    connect(socket, &QWebSocket::textMessageReceived, [this, socket, request](const QString& message) {
        const auto answer = handle(toJson(message), username(request.session));
        socket->sendTextMessage(answer);
    });

    connect(socket, &QWebSocket::readChannelFinished, this, [this, socket] {
        unmount(socket);
    });

    m_gameListReceivers.push_back(socket);
}

void Lobby::unmount(QWebSocket* socket)
{
    m_gameListReceivers.erase(std::find(m_gameListReceivers.begin(), m_gameListReceivers.end(), socket));
    Route::unmount(socket);
}

void Lobby::resendGameList()
{
    // TODO: filter games not yet running
    // TODO: send list to m_gameListReceivers
}

QString Lobby::handle(const QJsonObject& message, const QString& playerName)
{
    if (!message.contains("request"))
    {
        const auto error = QString("Invalid request: value 'request' is not set");
        return generateError(error, InvalidRequest);
    }

    if (message["request"] == "create_game")
    {
        return handleCreate(playerName);
    }

    if (message["request"] == "join_game")
    {
        if (!message.contains("data"))
        {
            const auto error = QString("Invalid request: 'data' required");
            return generateError(error, InvalidRequest);
        }

        return handleJoin(message["data"], playerName);
    }

    const auto error = QString("Unsupported action: '%1'.").arg(message["request"].toString());
    return generateError(error, UnsupportedAction);
}

QString Lobby::handleCreate(const QString& playerName)
{
    const auto gameID = createNewGame();

    auto game = getGame(gameID);
    game->players.push_back(PlayerState(playerName));

    return answer("create_game", gameID);
}

QString Lobby::handleJoin(const QJsonValue& data, const QString& playerName)
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

    const int gameID = idVal.toInt(-1);

    if (gameID == -1)
    {
        const auto error = QString("Invalid request: 'data.game_id' has to be a whole number");
        return generateError(error, InvalidRequest);
    }

    auto game = getGame(gameID);

    if (!game)
    {
        const auto error = QString("Internal Error: a game with id %1 does not exist").arg(gameID);
        return generateError(error, InternalError);
    }

    if (!(game->currentPlayer == -1))
    {
        const auto error = QString("Internal Error: the game %1 already started").arg(gameID);
        return generateError(error, InternalError);
    }

    if (std::any_of(game->players.begin(), game->players.end(), [&playerName](const PlayerState& state){return state.name == playerName;}))
    {
        const auto error = QString("Internal Error: the player already joined the game").arg(gameID);
        return generateError(error, InternalError);
    }

    game->players.push_back(PlayerState(playerName));

    return answer("join_game", gameID);
}

QString Lobby::answer(const QString& request, const int gameID)
{
    QJsonObject answerObj;
    answerObj["name"] = request;
    answerObj["data"] = QJsonObject({{"game_id", gameID}});
    return QJsonDocument(answerObj).toJson();
}
