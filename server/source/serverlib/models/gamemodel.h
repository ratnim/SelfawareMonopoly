#pragma once

#include <vector>

#include <QObject>

#include <game/game.h>

class GameModel : public QObject
{
    Q_OBJECT

public:
    int createGame(const QString& label);
    int numberOfGames() const;
    Game& openGame(int gameId);

    static GameModel& instance();

signals:
    void onCreateGame(Game& game);

protected:
    std::vector<std::unique_ptr<Game>> m_games;
};
