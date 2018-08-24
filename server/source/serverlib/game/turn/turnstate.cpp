#include "turnstate.h"

#include <game/game.h>

#include <utils/exception.h>

TurnState::TurnState(Game* game)
    : m_game(game)
{
}

void TurnState::gameStart()
{
    InvalidRequest();
}

void TurnState::playerJoin(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::playerReady(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::rollDice(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::endTurn(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::possibleRequests(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::InvalidRequest()
{
    throw Exception("You are not allowed to perform this action.", Error::InvalidRequest);
}
