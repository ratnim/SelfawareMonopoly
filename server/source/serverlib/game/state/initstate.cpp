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
    if (m_status.size() >= maximumPlayers)
    {
        throw Exception("The maximum number of players is already joined.");
    }

    if (m_status.find(playerName) != m_status.end())
    {
        throw Exception("The player is already in the game.");
    }

    m_status[playerName] = false;
    emit m_game->onPlayerJoin(playerName);
}

void InitState::ready(const QString& playerName)
{
    if (m_status[playerName])
    {
        throw Exception("The player is already ready.");
    }

    m_status[playerName] = true;
    emit m_game->onPlayerReady(playerName);
}

void InitState::start()
{
    if (m_status.size() < minimumPlayers)
    {
        throw Exception("The minimum amount of players is not reached.");
    }

    for (const auto& elem : m_status)
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
    for (auto& player : m_status)
    {
        order.push_back(player.first);
    }
    // TODO random shuffle
    return order;
}
