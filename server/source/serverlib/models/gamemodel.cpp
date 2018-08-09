#include "gamemodel.h"

#include <models/boardmodel.h>
#include <utils/exception.h>

GameObject::GameObject(const QString& label, Board board)
    : game(std::move(board))
	, watcher(game)
    , info(game, label)
{
}

int GameModel::createGame(const QString& label, const QString& boardfile)
{
    Board board({});
    if (!boardfile.isEmpty())
		auto board = std::move(BoardModel::instance().newBoard(boardfile));

    m_games.emplace_back(std::make_unique<GameObject>(label, std::move(board)));
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
