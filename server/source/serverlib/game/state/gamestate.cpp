#include "gamestate.h"

#include <utils/exception.h>

void GameState::join(const QString& playerName)
{
    InvalidRequest();
}

void GameState::ready(const QString& playerName)
{
    InvalidRequest();
}

void GameState::start()
{
    InvalidRequest();
}

void GameState::rollDice(const QString& playerName)
{
    InvalidRequest();
}

void GameState::endTurn(const QString& playerName)
{
    InvalidRequest();
}

void GameState::InvalidRequest()
{
    throw Exception("This action is currently not allowed by the game.", Error::InvalidRequest);
}
