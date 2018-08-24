#include "turnstate.h"

#include <QJsonObject>

#include <utils/exception.h>

TurnState::TurnState(GameLogic* logic)
    : m_logic(logic),
	m_game(logic->m_game)
{
}

TurnState::TurnState(Game* game)
    : m_logic(nullptr), m_game(game)
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
