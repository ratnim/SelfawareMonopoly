#include "initstate.h"

#include <QJsonArray>
#include <QJsonObject>

#include <game/game.h>
#include <game/turn/possiblerequest.h>
#include <game/turn/movestate.h>
#include <utils/exception.h>

namespace
{
int minimumPlayers = 2;
int maximumPlayers = 6;
int startMoney = 1500;
}

InitState::InitState(Game* game)
    : TurnState(game)
{
}

void InitState::possibleRequests(const QString& playerName)
{
    QJsonArray requests;

    if (!m_playersReady[playerName])
    {
        requests.append(PossibleRequest::playerReady().toJson());
    }
    else if (gameIsStartable())
    {
        requests.append(PossibleRequest::gameStart().toJson());
    }

    emit m_game->onPossibleRequests(playerName, requests);
}

void InitState::requestPlayerJoin(const QString& playerName)
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

    handleGameStart();
}

std::vector<Player> InitState::joinedPlayers()
{
    std::vector<Player> order;
    for (auto& player : m_playersReady)
    {
        order.push_back(std::move(player.first));
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

void InitState::handleGameStart()
{

	for (auto& player : joinedPlayers())
	{
        m_game->bank().createAccount(player.name(), startMoney);
	}
    m_game->players() = RingBuffer<Player>(std::move(joinedPlayers()));

    emit m_game->onGameStart();
    emit m_game->onTurnChange(m_game->currentPlayer().name());

    m_game->stateChange<MoveState>(this);
}

void InitState::broadcastPossibleRequests()
{
    for (auto& player : m_playersReady)
    {
        possibleRequests(player.first);
    }
}
