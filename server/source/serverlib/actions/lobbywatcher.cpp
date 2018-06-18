#include "lobbywatcher.h"

#include <QJsonDocument>

#include <models/gamemodel.h>

std::unique_ptr<LobbyWatcher> StaticStorage<LobbyWatcher>::s_model;

LobbyWatcher::LobbyWatcher()
{
    watchAllGames();
    connect(&GameModel::instance(), &GameModel::onCreateGame, this, &LobbyWatcher::watchGame);
}

QString LobbyWatcher::message()
{
    QJsonArray games;

    const auto numberOfGames = GameModel::instance().numberOfGames();
    for (int i = 0; i < numberOfGames; ++i)
    {
        games.push_back(toJson(i));
    }

    return answer(games);
}

LobbyWatcher& LobbyWatcher::instance()
{
    static LobbyWatcher watcher;
    return watcher;
}

void LobbyWatcher::watchAllGames()
{
    auto& model = GameModel::instance();
    for (int i = 0; i < model.numberOfGames(); ++i)
    {
        watchGame(model.open(i).info);
    }
}

void LobbyWatcher::watchGame(const GameInfo& info)
{
    connect(&info, &GameInfo::change, this, &LobbyWatcher::updateLobby);
}

void LobbyWatcher::updateLobby()
{
    emit send(message());
}

QJsonObject LobbyWatcher::toJson(int gameId)
{
    auto& game = GameModel::instance().open(gameId).info;

    QJsonObject description;
    description["game_id"] = gameId;
    description["player_list"] = toArray(game.players());
    description["game_status"] = game.state();
    description["game_label"] = game.label();
    return description;
}

QJsonArray LobbyWatcher::toArray(const std::vector<QString>& players)
{
    QJsonArray array;
    for (auto &player : players)
    {
        array.push_back(player);
    }
    return array;
}

QString LobbyWatcher::answer(const QJsonArray& games)
{
    QJsonObject answer({ { "name", "game_list" } });
    answer["data"] = QJsonObject{ { "games", games } };

    return QJsonDocument(answer).toJson();
}
