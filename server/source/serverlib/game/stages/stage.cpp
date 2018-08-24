#include "stage.h"

#include <utils/exception.h>

void Stage::playerJoin(const QString& playerName)
{
    InvalidRequest();
}

void Stage::playerReady(const QString& playerName)
{
    InvalidRequest();
}

void Stage::gameStart()
{
    InvalidRequest();
}

void Stage::rollDice(const QString& playerName)
{
    InvalidRequest();
}

void Stage::endTurn(const QString& playerName)
{
    InvalidRequest();
}

void Stage::possibleRequests(const QString& playerName)
{
    InvalidRequest();
}

void Stage::InvalidRequest()
{
    throw Exception("This action is currently not allowed by the game.", Error::InvalidRequest);
}
