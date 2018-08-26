#include "lobbyconnection.h"

#include <QJsonDocument>

#include <watchers/lobbywatcher.h>
#include <models/accountmodel.h>
#include <models/gamemodel.h>
#include <utils/exception.h>

LobbyConnection::LobbyConnection(QWebSocket* parent, const ConnectionRequest& request)
    : Connection(parent)
    , m_playerName(AccountModel::instance().username(request.session))
{
    m_requests["create_game"] = [this](const QJsonValue& data) {
        createGame(data);
    };

    watchLobby();
}

void LobbyConnection::watchLobby()
{
    auto& watcher = LobbyWatcher::instance();

    emit broadcast(watcher.message());
    connect(&watcher, &Watcher::broadcast, this, &Watcher::broadcast);
}

void LobbyConnection::createGame(const QJsonValue& body)
{
    const auto label = body[QString("game_label")].toString();
    if (label.isEmpty())
    {
        throw Exception("data.game_label is missing.", Error::MalformedRequest);
    }

	QString boardFile = "berlin.json";
    const auto gameId = GameModel::instance().createGame(label, boardFile);
    emit broadcast(createGameAnswer(gameId));
}

QString LobbyConnection::createGameAnswer(int gameId)
{
    QJsonObject answer({ { "name", "create_game" } });
    answer[QString("data")] = QJsonObject({ { "game_id", gameId } });

    return QJsonDocument(answer).toJson();
}
