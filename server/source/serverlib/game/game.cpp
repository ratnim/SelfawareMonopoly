#include "game.h"

#include <utils/exception.h>

namespace
{
int minimumPlayers = 2;
int maximumPlayers = 6;
}

Game::Game(const QString& label)
    : m_watcher(*this)
    , m_label(label)
{
}

const std::map<QString, Player>& Game::players() const
{
    return m_players;
}

Game::State Game::state() const
{
    return m_state;
}

QString Game::label() const
{
    return m_label;
}

GameWatcher& Game::watcher()
{
    return m_watcher;
}

void Game::join(const QString& playerName)
{
    if (m_state != START)
    {
        throw Exception("Invalid Request: The game already started.");
    }

    if (m_players.size() >= maximumPlayers)
    {
        throw Exception("Invalid Request: The maximum number of players is already joined.");
    }

    if (m_players.find(playerName) != m_players.end())
    {
        throw Exception("Invalid Request: The player is already in the game.");
    }

    m_players[playerName];
    emit onPlayerJoin(playerName);
}

void Game::ready(const QString& playerName)
{
    if (m_state != START)
    {
        throw Exception("Invalid Request: The game already started.");
    }

    if (m_players[playerName].ready)
    {
        throw Exception("Invalid Request: The player is already ready.");
    }

    m_players[playerName].ready = true;
    emit onPlayerReady(playerName);
}

void Game::start()
{
    if (m_state != START)
    {
        throw Exception("Invalid Request: The game already started.");
    }

    if (m_players.size() < minimumPlayers)
    {
        throw Exception("Invalid Request: The minimum amount of players is not reached.");
    }

    for (const auto& elem : m_players)
    {
        if (!elem.second.ready)
        {
            throw Exception("Invalid Request: Not every player is ready.");
        }
    }

    m_state = RUNNING;
    for (auto& player : m_players)
    {
        m_turnOrder.push_back(player.first);
    }
    m_turn = 0;

    emit onGameStart();

    canRoll = true;
    reRollCount = 0;
    emit onTurnChange(m_turnOrder[m_turn]);
}

void Game::rollDice(const QString& playerName)
{
    if (m_state != RUNNING)
    {
        throw Exception("Invalid Request: The game did not start.");
    }

    if (m_turnOrder[m_turn] != playerName)
    {
        throw Exception("Invalid Request: Not your turn.");
    }

    if (!canRoll)
    {
        throw Exception("Invalid Request: You can not roll anymore.");
    }

    int d1 = rand() % 6 + 1;
    int d2 = rand() % 6 + 1;
    if (d1 == d2)
    {
        ++reRollCount;
    }
    else
    {
        canRoll = false;
    }

    if (reRollCount == 3)
    {
        //move to jail
    }
    else
    {
        emit onRollDice(d1, d2);
        emit onPlayerMove(d1 + d2);
    }
}

void Game::endTurn(const QString& playerName)
{
    if (m_state != RUNNING)
    {
        throw Exception("Invalid Request: The game did not start.");
    }

    if (m_turnOrder[m_turn] != playerName)
    {
        throw Exception("Invalid Request: Not your turn.");
    }

    if (canRoll)
    {
        throw Exception("Invalid Request: You have to roll first.");
    }

    canRoll = true;
    reRollCount = 0;

    m_turn = (m_turn+1) % m_players.size();
    emit onTurnChange(m_turnOrder[m_turn]);
}