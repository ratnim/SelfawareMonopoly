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
