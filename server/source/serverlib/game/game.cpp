#include "game.h"

#include <game/turn/initstate.h>

Game::Game(Board gameBoard)
    : m_board(std::move(gameBoard))
	, m_players({})
{
    stateChange<InitState>(this);
}

void Game::playerJoin(const QString& playerName)
{
    m_state->playerJoin(playerName);
}

void Game::gameBoard()
{
    emit onBoardRequest(m_board.description());
}

void Game::playerReady(const QString& playerName)
{
    m_state->playerReady(playerName);
}

void Game::gameStart()
{
    m_state->gameStart();
}

void Game::rollDice(const QString& playerName)
{
    m_state->rollDice(playerName);
}

void Game::endTurn(const QString& playerName)
{
    m_state->endTurn(playerName);
}

void Game::possibleRequests(const QString& playerName)
{
    m_state->possibleRequests(playerName);
}

RingBuffer<Player>& Game::players()
{
    return m_players;
}

Player& Game::currentPlayer()
{
    return m_players();
}
