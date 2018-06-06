#include "gameroute.h"

#include <models/accountmodel.h>
#include <models/gamemodel.h>

GameRoute::GameRoute(QObject* parent, const Request& request)
    : Route(parent)
    , m_playerName(AccountModel::instance().username(request.session))
{
    auto& game = GameModel::instance().openGame(request.gameId);
    m_actions["join_game"] = [&game, this](const QJsonValue&) { game.join(m_playerName); };
    m_actions["player_ready"] = [&game, this](const QJsonValue&) { game.ready(m_playerName); };
    m_actions["game_start"] = [&game, this](const QJsonValue&) { game.start(); };

    m_actions["roll_dice"] = [&game, this](const QJsonValue&) { game.rollDice(m_playerName); };
    m_actions["end_turn"] = [&game, this](const QJsonValue&) { game.endTurn(m_playerName); };

    watchGame(game.watcher());
}

void GameRoute::watchGame(GameWatcher& watcher)
{
    for (const auto& message : watcher.messages())
    {
        emit send(message);
    }
    connect(&watcher, &Watcher::send, this, &Watcher::send);
}
