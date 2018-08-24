#include "initstage.h"

#include <QJsonArray>
#include <QJsonObject>

#include <game/game.h>
#include <game/turn/possiblerequest.h>
#include <game/stages/runstage.h>
#include <utils/exception.h>

namespace
{
int minimumPlayers = 2;
int maximumPlayers = 6;
}

InitState::InitState(Game* game)
    : TurnState(game)
{
}

void InitState::playerJoin(const QString& playerName)
{
    if (maximalPlayersJoined())
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

void InitState::playerReady(const QString& playerName)
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

void InitState::gameStart()
{
    if (!minimalPlayersJoined())
    {
        throw Exception("The minimum amount of players is not reached.");
    }

    if (!allPlayersReady())
    {
        throw Exception("Not every player is ready.");
    }

    m_game->stateChange<StartState>(this, joinedPlayers());
}

std::vector<Player> InitState::joinedPlayers()
{
    std::vector<Player> order;
    for (auto& player : m_playersReady)
    {
        order.push_back(player.first);
    }
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

bool InitState::maximalPlayersJoined() const
{
    return m_playersReady.size() >= maximumPlayers;
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
    requests.append(PossibleRequest::gameStart().toJson());

    for (auto& player : m_playersReady)
    {
        emit m_game->onPossibleRequests(player.first, requests);
    }
}

void InitState::broadcastPlayerReadyRequest() const
{
    QJsonArray requests;
    requests.append(PossibleRequest::playerReady().toJson());

    for (auto& player : m_playersReady)
    {
		if (!player.second)
		{
			emit m_game->onPossibleRequests(player.first, requests);
		}
		else
		{
            emit m_game->onPossibleRequests(player.first, {});
		}
    }
}
