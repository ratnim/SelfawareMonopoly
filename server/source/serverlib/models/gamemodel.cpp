#include "gamemodel.h"

#include <utils/exception.h>

int GameModel::createGame(const QString& label)
{
    m_games.push_back(std::make_unique<Game>(label));
    emit onCreateGame(*m_games.back());

    return static_cast<int>(m_games.size() - 1);
}

int GameModel::numberOfGames() const
{
    return static_cast<int>(m_games.size());
}

Game& GameModel::openGame(int gameId)
{
    if (gameId >= 0 && gameId < m_games.size())
    {
        return *m_games[gameId];
    }
    throw Exception("The game id is not valid.");
}
