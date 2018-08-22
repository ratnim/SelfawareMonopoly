#include "initstate.h"

#include <QJsonArray>
#include <QJsonObject>

#include <game/game.h>
#include <game/state/runstate.h>
#include <utils/exception.h>

namespace
{
int minimumPlayers = 2;
int maximumPlayers = 6;
}

InitState::InitState(Game* game)
    : m_game(game)
{
}

void InitState::join(const QString& playerName)
{
    if (m_playersReady.size() >= maximumPlayers)
    {
        throw Exception("The maximum number of players is already joined.");
    }

    if (m_playersReady.find(playerName) != m_playersReady.end())
    {
        throw Exception("The player is already in the game.");
    }

    m_playersReady[playerName] = false;
    emit m_game->onPlayerJoin(playerName);
    broadcastPossibleRequests();
}

void InitState::ready(const QString& playerName)
{
    if (m_playersReady.find(playerName) == m_playersReady.end())
    {
        throw Exception("The player is not in the game.");
    }

    if (m_playersReady[playerName])
    {
        throw Exception("The player is already ready.");
    }

    m_playersReady[playerName] = true;
    emit m_game->onPlayerReady(playerName);
    broadcastPossibleRequests();
}

void InitState::start()
{
    if (!minimalPlayersJoined())
    {
        throw Exception("The minimum amount of players is not reached.");
    }

    if (!allPlayersReady())
    {
        throw Exception("Not every player is ready.");
    }

    m_game->stateChange<RunState>(m_game, turnOrder());
}

std::vector<Player> InitState::turnOrder()
{
    std::vector<Player> order;
    for (auto& player : m_playersReady)
    {
        order.push_back(player.first);
    }
    // TODO random shuffle
    return order;
}

bool InitState::allPlayersReady() const
{
    for (const auto& elem : m_playersReady)
    {
        if (!elem.second)
        {
            return false;
        }
    }
    return true;
}

bool InitState::gameIsStartable() const
{
    return minimalPlayersJoined() && allPlayersReady();
}

bool InitState::minimalPlayersJoined() const
{
    return m_playersReady.size() >= minimumPlayers;
}

void InitState::broadcastPossibleRequests() const
{
    if (gameIsStartable())
    {
        broadcastGameIsStartable();
	}
	else
	{
        broadcastPlayerReadyRequest();
	}
}

void InitState::broadcastGameIsStartable() const
{
    QJsonArray requests;
    requests.append(createPossibleRequest("game_start"));

    for (auto& player : m_playersReady)
    {
        m_game->possibleRequests(player.first, requests);
    }
}

void InitState::broadcastPlayerReadyRequest() const
{
    QJsonArray requests;
    requests.append(createPossibleRequest("player_ready"));

    for (auto& player : m_playersReady)
    {
		if (!player.second)
		{
			m_game->possibleRequests(player.first, requests);
		}
		else
		{
            m_game->possibleRequests(player.first, {});
		}
    }
}

QJsonObject InitState::createPossibleRequest(const QString& requestName) const
{
    QJsonObject request;
    request["request"] = requestName;
    request["data"] = QJsonObject{};
    return request;
}
