#include "gameconnection.h"

#include <models/accountmodel.h>
#include <models/gamemodel.h>

GameConnection::GameConnection(QWebSocket* parent, const ConnectionRequest& request)
    : Connection(parent)
    , m_playerName(AccountModel::instance().username(request.session))
{
    auto& compound = GameModel::instance().open(request.gameId);
    auto& game = compound.game;

    m_requests["join_game"] = [&game, this](const QJsonValue&) { game.join(m_playerName); };
    m_requests["game_board"] = [&game, this](const QJsonValue&) { game.board(); };
    m_requests["player_ready"] = [&game, this](const QJsonValue&) { game.ready(m_playerName); };
    m_requests["game_start"] = [&game, this](const QJsonValue&) { game.start(); };

    m_requests["roll_dice"] = [&game, this](const QJsonValue&) { game.rollDice(m_playerName); };
    m_requests["end_turn"] = [&game, this](const QJsonValue&) { game.endTurn(m_playerName); };

	m_requests["possible_requests"] = [&game, this](const QJsonValue&) { game.possibleRequests(m_playerName); };

    watchGame(compound.watcher);
}

void GameConnection::watchGame(GameWatcher& watcher)
{
    for (const auto& message : watcher.messages())
    {
        emit broadcast(message);
    }
    connect(&watcher, &Watcher::broadcast, this, &Watcher::broadcast);
    connect(&watcher, &GameWatcher::broadcastPlayerMessage, this, &GameConnection::broadcastFiltered);
}

void GameConnection::broadcastFiltered(const QString& player, const QString& message)
{
	if (player == m_playerName)
	{
        emit broadcast(message);
	}
}
