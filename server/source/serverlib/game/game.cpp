#include "game.h"

#include <QJsonObject>

#include <game/stages/initstage.h>
#include <models/boardmodel.h>

Game::Game(Board board)
    : m_board(std::move(board))
{
	stateChange<InitStage>(this);
}

void Game::join(const QString& playerName)
{
    m_state->join(playerName);
}

void Game::board()
{
    emit onBoardRequest(m_board.description());
}

void Game::ready(const QString& playerName)
{
    m_state->ready(playerName);
}

void Game::start()
{
    m_state->start();
}

void Game::rollDice(const QString& playerName)
{
    m_state->rollDice(playerName);
}

void Game::endTurn(const QString& playerName)
{
    m_state->endTurn(playerName);
}

void Game::possibleRequests(const QString& playerName, const QJsonArray& requests)
{
    emit onPossibleRequests(playerName, requests);
}