#include "game.h"

const std::vector<QString>& Game::players() const
{
    return m_players;
}

Game::State Game::state() const
{
    return m_state;
}

void Game::join(const QString& playerName)
{

}
