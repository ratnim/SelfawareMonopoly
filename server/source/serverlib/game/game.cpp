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
    , m_state(START)
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

    auto player = m_players[playerName];

    int d1 = rand() % 6 + 1;
    int d2 = rand() % 6 + 1;
    emit onRollDice(d1, d2);

    if (d1 == d2)
    {
        ++reRollCount;
        if (player.inJail)
        {
            player.inJail = false;
            canRoll = false;
        }
    }
    else
    {
        canRoll = false;
    }

    const int goToJailPosition = 30;
    const int gameEndField = 40;

    if (reRollCount == 3)
    {
        goToJail(player);
    }
    else
    {
        auto sum = d1 + d2;
        player.position += sum;
        emit onPlayerMove(sum);

        // handle go to jail field
        if (player.position == goToJailPosition)
        {
            goToJail(player);
        }

        // handle game end
        if (player.position >= gameEndField)
        {
            m_state = FINISHED;
            emit onGameEnd();
        }
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

    m_turn = (m_turn + 1) % m_players.size();
    emit onTurnChange(m_turnOrder[m_turn]);

    auto player = m_players[m_turnOrder[m_turn]];

    if (player.inJail)
    {
        ++player.jailTurns;
        if (player.jailTurns >= 3)
        {
            player.inJail = false;
        }
    }
}

void Game::goToJail(Player& player)
{
    const int jailPosition = 10;

    auto distance = jailPosition - player.position;
    player.position = jailPosition;
    emit onPlayerMove(distance);

    player.inJail = true;
    player.jailTurns = 0;
}
