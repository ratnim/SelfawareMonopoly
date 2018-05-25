#pragma once

#include <vector>
#include <map>

#include <QString>

struct PlayerState
{
    PlayerState(const QString& playerName)
    : name(playerName)
    {}

    QString name;
    unsigned int position;
    unsigned int jailTime;
};

struct BoardState
{
    std::vector<PlayerState> players;
    int currentPlayer = -1;
    unsigned int dice1, dice2;
};

// returns ID
int createNewGame();

BoardState * getGame(const int id);

class GameState
{
public:
//    GameState();
//
//    QByteArray handle(const Request& request);
//
//protected:
//    QByteArray handleLobby(const Request& request);
//    QByteArray handleGame(const Request& request);
//
//    QJsonObject toAction(const QString& name);
//
//    void gameJoin(const QJsonObject& request);
//    void gameStart();
//    void turnStart();
//    void turnEnd();
//    void rollDice();
//
//    int turn;
//    std::vector<QString> playerNames;
//    std::vector<QJsonObject> actions;
};
