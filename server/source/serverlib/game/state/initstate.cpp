#include "initstate.h"

#include <game/game.h>
#include <game/state/runstate.h>
#include <utils/exception.h>

namespace
{
int minimumPlayers = 2;
int maximumPlayers = 6;
}

InitState::InitState(GameState* old, Game* game)
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
}

void InitState::start()
{
    if (m_playersReady.size() < minimumPlayers)
    {
        throw Exception("The minimum amount of players is not reached.");
    }

    for (const auto& elem : m_playersReady)
    {
        if (!elem.second)
        {
            throw Exception("Not every player is ready.");
        }
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
