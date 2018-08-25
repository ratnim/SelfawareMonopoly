#pragma once

#include <game/state/gamestate.h>
#include <game/board/board.h>
#include <utils/budhist.h>

class Game : public QObject, public Budhist<GameState>
{
    Q_OBJECT

public:
    Game(Board board = Board({}));

    void join(const QString& playerName);
    void board();
    void ready(const QString& playerName);
    void start();

    void rollDice(const QString& playerName);
    void pay(const QString& playerName);
    void ignore(const QString& playerName);
    void draw(const QString& playerName);
    void endTurn(const QString& playerName);

signals:
    void onBoardRequest(const QJsonObject& board);
    void onPlayerJoin(const QString& playerName);
    void onPlayerReady(const QString& playerName);

    void onGameStart();
    void onGameEnd();

    void onRollDice(const QString& playerName, int d1, int d2);
    void onPlayerMove(const QString& playerName, int distance);
    void onTurnChange(const QString& newMovingPlayer);

    void onEnterJail(const QString& playerName);
    void onLeaveJail(const QString& playerName);

protected:
    Board m_board;
};
