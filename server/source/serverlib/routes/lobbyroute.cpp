#include "lobbyroute.h"

#include <QJsonDocument>

#include <actions/lobbywatcher.h>
#include <models/accountmodel.h>
#include <models/gamemodel.h>
#include <utils/exception.h>

LobbyRoute::LobbyRoute(QWebSocket* socket, const Request& request)
    : Route(socket)
    , m_playerName(AccountModel::instance().username(request.session))
{
    m_actions["create_game"] = [this, socket](const QJsonValue& data) {
        createGame(socket, data);
    };

    watchLobby(socket);
}

void LobbyRoute::watchLobby(QWebSocket* socket)
{
    auto& watcher = LobbyWatcher::instance();

    socket->sendTextMessage(watcher.message());
    connect(&watcher, &Watcher::send, socket, &QWebSocket::sendTextMessage);
}

void LobbyRoute::createGame(QWebSocket* socket, const QJsonValue& body)
{
    const auto label = body["game_label"].toString();
    if (label.isEmpty())
    {
        throw Exception("Malformed Request: data.game_label is missing.");
    }

    const auto gameId = GameModel::instance().createGame(label);
    socket->sendTextMessage(createGameAnswer(gameId));
}

QString LobbyRoute::createGameAnswer(int gameId)
{
    QJsonObject answer({ { "name", "create_game" } });
    answer["data"] = QJsonObject({ { "game_id", gameId } });

    return QJsonDocument(answer).toJson();
}
