#include "gamemodel.h"

#include <utils/exception.h>

int GameModel::createGame()
{
    m_games.push_back(std::make_unique<Game>());
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
    throw Exception("Invalid Request: The game id is not valid.");
}

GameModel& GameModel::instance()
{
    static GameModel model;
    return model;
}
