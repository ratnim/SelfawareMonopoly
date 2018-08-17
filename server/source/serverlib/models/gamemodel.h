#pragma once

#include <game/gameinfo.h>
#include <game/board/board.h>
#include <utils/staticstorage.h>
#include <watchers/gamewatcher.h>

struct GameObject
{
    GameObject(const QString& label, Board board);

    Game game;
    GameWatcher watcher;
    GameInfo info;
};

class GameModel : public QObject, public StaticStorage<GameModel>
{
    Q_OBJECT
public:
    int createGame(const QString& label, const QString& boardfile = "");
    int numberOfGames() const;
    GameObject& open(int gameId);

signals:
    void onCreateGame(const GameInfo& info);

protected:
    std::vector<std::unique_ptr<GameObject>> m_games;
};
