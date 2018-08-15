#pragma once

#include <game/game.h>

class GameInfo : public QObject
{
    Q_OBJECT
public:
    enum GameState
    {
        INTIALIZED,
        STARTED,
        FINISHED
    };

    GameInfo(const Game& game, const QString& label);

    QString label() const;
    GameState state() const;
    std::vector<QString> players() const;

signals:
    void change();

protected:
    void playerJoin(const QString& playerName);
    void gameStart();
    void gameEnd();

    const QString m_label;
    GameState m_state;
    std::vector<QString> m_players;
};
