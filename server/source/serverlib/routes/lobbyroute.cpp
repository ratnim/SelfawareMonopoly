#include "lobbyroute.h"

#include <QJsonDocument>

#include <watchers/lobbywatcher.h>
#include <models/accountmodel.h>
#include <models/gamemodel.h>
#include <utils/exception.h>

LobbyRoute::LobbyRoute(QWebSocket* parent, const Request& request)
    : Route(parent)
    , m_playerName(AccountModel::instance().username(request.session))
{
    m_actions["create_game"] = [this](const QJsonValue& data) {
        createGame(data);
    };

    watchLobby();
}

void LobbyRoute::watchLobby()
{
    auto& watcher = LobbyWatcher::instance();

    emit send(watcher.message());
    connect(&watcher, &Watcher::send, this, &Watcher::send);
}

void LobbyRoute::createGame(const QJsonValue& body)
{
    const auto label = body[QString("game_label")].toString();
    if (label.isEmpty())
    {
        throw Exception("data.game_label is missing.", Error::MalformedRequest);
    }

    const auto gameId = GameModel::instance().createGame(label);
    emit send(createGameAnswer(gameId));
}

QString LobbyRoute::createGameAnswer(int gameId)
{
    QJsonObject answer({ { "name", "create_game" } });
    answer[QString("data")] = QJsonObject({ { "game_id", gameId } });

    return QJsonDocument(answer).toJson();
}
