#include "gameinfo.h"

GameInfo::GameInfo(const Game& game, const QString& label)
    : m_label(label)
    , m_state("initialized")
{
    connect(&game, &Game::onGameStart, this, &GameInfo::gameStart);
    connect(&game, &Game::onGameEnd, this, &GameInfo::gameEnd);
    connect(&game, &Game::onPlayerJoin, this, &GameInfo::playerJoin);
}

QString GameInfo::label() const
{
    return m_label;
}

QString GameInfo::state() const
{
    return m_state;
}

std::vector<QString> GameInfo::players() const
{
    return m_players;
}

void GameInfo::playerJoin(const QString& playerName)
{
    m_players.push_back(playerName);
    emit change();
}

void GameInfo::gameStart()
{
    m_state = "started";
    emit change();
}

void GameInfo::gameEnd()
{
    m_state = "finished";
    emit change();
}
