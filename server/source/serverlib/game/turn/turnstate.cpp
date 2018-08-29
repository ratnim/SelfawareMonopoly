#include "turnstate.h"

#include <QJsonArray>

#include <game/game.h>

#include <utils/exception.h>

TurnState::TurnState(Game* game)
    : m_game(game)
{
}

void TurnState::requestGameStart()
{
    InvalidRequest();
}

void TurnState::requestPlayerJoin(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::requestPlayerReady(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::requestRollDice(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::requestEndTurn(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::requestPossibleRequests(const QString& playerName)
{
    emit m_game->onPossibleRequests(playerName, QJsonArray{});
}

void TurnState::InvalidRequest()
{
    throw Exception("You are not allowed to perform this action.", Error::InvalidRequest);
}

bool TurnState::playersTurn(const QString& playerName) const
{
    return playerName == m_game->currentPlayer().name();
}

void TurnState::broadcastPossibleRequests()
{
    for (auto& player : m_game->players().storage())
    {
        requestPossibleRequests(player.name());
    }
}

void TurnState::ensurePlayersTurn(const QString& playerName) const
{
    if (!playersTurn(playerName))
    {
        throw Exception("Not your turn.", Error::InvalidRequest);
    }
}
