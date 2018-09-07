#include "gameconnection.h"

#include <models/accountmodel.h>
#include <models/gamemodel.h>

GameConnection::GameConnection(QWebSocket* parent, const ConnectionRequest& request)
    : Connection(parent)
    , m_playerName(AccountModel::instance().username(request.session))
{
    auto& compound = GameModel::instance().open(request.gameId);
    auto& game = compound.game;

    m_requests["join_game"] = [&game, this](const QJsonValue&) { game.requestPlayerJoin(m_playerName); };
    m_requests["game_board"] = [&game, this](const QJsonValue&) { game.requestGameBoard(); };
    m_requests["player_ready"] = [&game, this](const QJsonValue&) { game.requestPlayerReady(m_playerName); };
    m_requests["game_start"] = [&game, this](const QJsonValue&) { game.requestGameStart(); };

    m_requests["roll_dice"] = [&game, this](const QJsonValue&) { game.requestRollDice(m_playerName); };
    m_requests["end_turn"] = [&game, this](const QJsonValue&) { game.requestEndTurn(m_playerName); };
    m_requests["buy_field"] = [&game, this](const QJsonValue& data) { game.requestBuyField(m_playerName, true); };
    m_requests["dont_buy_field"] = [&game, this](const QJsonValue& data) { game.requestBuyField(m_playerName, false); };
    m_requests["pay_debt"] = [&game, this](const QJsonValue& data) { game.requestPayDebt(m_playerName, data["beneficiary"].toString()); };

    m_requests["build_houses"] = [&game, this](const QJsonValue& data) {
        std::vector<std::pair<int,int>> pairs;

        for (const auto& [key, val] : data["building_sites"].toObject().toVariantMap().toStdMap())
        {
            pairs.emplace_back(key.toInt(), val.toInt());
        }

        game.requestChangeHouses(m_playerName, pairs);
    };

	m_requests["possible_requests"] = [&game, this](const QJsonValue&) { game.requestPossibleRequests(m_playerName); };

	m_requests["clicked_on_add"] = [&game, this](const QJsonValue& data) { game.watson().requestAddClick(m_playerName, data["add_name"].toString()); };

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
