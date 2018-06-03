#pragma once

#include <vector>

#include <QObject>

#include <game/game.h>

class GameModel : public QObject
{
    Q_OBJECT

public:
    int createGame();
    int numberOfGames() const;
    Game& openGame(int gameId);

    static GameModel& instance();

signals:
    void onCreateGame(Game& game);

protected:
    std::vector<std::unique_ptr<Game>> m_games;
};
