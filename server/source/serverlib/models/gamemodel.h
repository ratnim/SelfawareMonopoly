#pragma once

#include <game/gameinfo.h>
#include <watchers/gamewatcher.h>
#include <utils/staticstorage.h>

struct GameObject
{
    GameObject(const QString& label);

    Game game;
    GameWatcher watcher;
    GameInfo info;
};

class GameModel : public QObject, public StaticStorage<GameModel>
{
    Q_OBJECT
public:
    int createGame(const QString& label);
    int numberOfGames() const;
    GameObject& open(int gameId);

signals:
    void onCreateGame(const GameInfo& info);

protected:
    std::vector<std::unique_ptr<GameObject>> m_games;
};
