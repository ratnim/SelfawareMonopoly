#pragma once

#include <vector>

#include <QObject>

#include <game/game.h>
#include <utils/staticstorage.h>

class GameModel : public QObject, public StaticStorage<GameModel>
{
    Q_OBJECT

public:
    int createGame(const QString& label);
    int numberOfGames() const;
    Game& openGame(int gameId);

signals:
    void onCreateGame(Game& game);

protected:
    std::vector<std::unique_ptr<Game>> m_games;
};
