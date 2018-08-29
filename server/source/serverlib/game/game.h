#pragma once

#include <queue>

#include <QJsonObject>

#include <utils/budhist.h>
#include <utils/ringbuffer.h>

#include <game/bank/bank.h>
#include <game/board/board.h>

#include <game/dices.h>
#include <game/player.h>
#include <game/turn/turnstate.h>

class Game : public QObject, public Budhist<TurnState>
{
    Q_OBJECT

public:
    Game(Board gameBoard = Board({}));

    void playerJoin(const QString& playerName);

    void gameBoard();
    void playerReady(const QString& playerName);
    void gameStart();

    void rollDice(const QString& playerName);
    void endTurn(const QString& playerName);

    void possibleRequests(const QString& playerName);

    Dices currentPlayerRollDices();
    void jailCurrentPlayer();

    RingBuffer<Player>& players();
    Player& currentPlayer();

    TurnState* state() const;
    Bank& bank();

    std::queue<Dices> watson_next_rolls;

    const int JAIL_POSITION = 10;
    const int GO_TO_JAIL_POSITION = 30;

signals:
    void onBoardRequest(const QJsonObject& gameBoard);
    void onPlayerJoin(const QString& playerName);
    void onPlayerReady(const QString& playerName);

    void onGameStart();
    void onGameEnd();

    void onRollDice(const QString& playerName, int d1, int d2);
    void onPlayerMove(const QString& playerName, int distance);
    void onTurnChange(const QString& newMovingPlayer);

    void onPossibleRequests(const QString& playerName, const QJsonArray& possibleRequests);

protected:
    Board m_board;
    Bank m_bank;
    RingBuffer<Player> m_players;
};
