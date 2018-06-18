#include "gamemodel.h"

#include <utils/exception.h>

std::unique_ptr<GameModel> StaticStorage<GameModel>::s_model;

GameObject::GameObject(const QString& label)
    : watcher(game)
    , info(game, label)
{
}

int GameModel::createGame(const QString& label)
{
    m_games.emplace_back(std::make_unique<GameObject>(label));
    emit onCreateGame(m_games.back()->info);
    return static_cast<int>(m_games.size() - 1);
}

int GameModel::numberOfGames() const
{
    return static_cast<int>(m_games.size());
}

GameObject& GameModel::open(int gameId)
{
    if (gameId >= 0 && gameId < m_games.size())
    {
        return *m_games[gameId];
    }
    throw Exception("The game id is not valid.");
}
