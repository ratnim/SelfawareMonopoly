#pragma once

#include <queue>

#include <QJsonObject>

#include <utils/budhist.h>
#include <utils/ringbuffer.h>

#include <game/bank/bank.h>
#include <game/board/board.h>
#include <game/cardstack.h>

#include <game/dices.h>
#include <game/player.h>
#include <game/turn/turnstate.h>

#include <game/watson.h>

class Game : public QObject, public Budhist<TurnState>
{
    Q_OBJECT

public:
    Game(std::vector<std::unique_ptr<Field>> fields = {});

    void requestPlayerJoin(const QString& playerName);

    void requestGameBoard();
    void requestPlayerReady(const QString& playerName);
    void requestGameStart();

    void requestRollDice(const QString& playerName);
    void requestEndTurn(const QString& playerName);
    void requestBuyField(const QString& playerName, bool buy);
    void requestChangeHouses(const QString& playerName, const std::vector<std::pair<int, int>>& newLevels);
    void requestPayDebt(const QString& debtor, const QString& beneficiary);

    void requestPossibleRequests(const QString& playerName);

    Dices doCurrentPlayerRollDices();
    void doCurrentPlayerGoToJail();
    void doCurrentPlayerMove(int distance);
    void doCurrentPlayerBuyField();
    void doCurrentPlayerChangeHouses(const std::vector<std::pair<int, int>>& newLevels);
    void doCurrentPlayerEarnMoney(int amount);
    void doTransferMoney(const QString& sender, const QString& reciever, int amount);

    RingBuffer<Player>& players();
    Player& currentPlayer();

    TurnState* state() const;
    Bank& bank();
    Board& board();
    CardStack& eventStack();
    CardStack& societyStack();
    Watson& watson();

signals:
    void onBoardRequest(const QJsonObject& gameBoard);
    void onPlayerJoin(const QString& playerName);
    void onPlayerReady(const QString& playerName);

    void onGameStart();
    void onGameEnd();

    void onRollDice(const QString& playerName, int d1, int d2);
    void onMoneyChange(const QString& playerName, int balance);
    void onPropertyChange(int id, const QString& owner, int consrtuctionLevel);
    void onPlayerMove(const QString& playerName, int index, const QString& type);
    void onTurnChange(const QString& newMovingPlayer);

    void onPossibleRequests(const QString& playerName, const QJsonArray& possibleRequests);

protected:
    Board m_board;
    Bank m_bank;
    CardStack m_eventStack;
    CardStack m_societyStack;
    RingBuffer<Player> m_players;
    Watson m_watson;
};
