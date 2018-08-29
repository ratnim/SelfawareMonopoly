#include "game.h"

#include <game/turn/initstate.h>

Game::Game(Board gameBoard)
    : m_board(std::move(gameBoard))
	, m_players({})
{
    connect(&m_bank, &Bank::onMoneyChange, this, &Game::onMoneyChange);

    stateChange<InitState>(this);
}

void Game::requestPlayerJoin(const QString& playerName)
{
    m_state->requestPlayerJoin(playerName);
}

void Game::requestGameBoard()
{
    emit onBoardRequest(m_board.description());
}

void Game::requestPlayerReady(const QString& playerName)
{
    m_state->playerReady(playerName);
}

void Game::requestGameStart()
{
    m_state->gameStart();
}

void Game::requestRollDice(const QString& playerName)
{
    m_state->rollDice(playerName);
}

void Game::requestEndTurn(const QString& playerName)
{
    m_state->endTurn(playerName);
}

void Game::requestPossibleRequests(const QString& playerName)
{
    m_state->possibleRequests(playerName);
}

Dices Game::doCurrentPlayerRollDices()
{
    currentPlayer().rolled();

    if (!watson_next_rolls.empty())
    {
        auto dices = watson_next_rolls.front();
        watson_next_rolls.pop();
        return dices;
    }

	return {};
}

void Game::doJailCurrentPlayer()
{
    currentPlayer().moveTo(JAIL_POSITION);
    emit onPlayerMove(currentPlayer().name(), JAIL_POSITION, "jump");
    
    currentPlayer().jail();
}

RingBuffer<Player>& Game::players()
{
    return m_players;
}

Player& Game::currentPlayer()
{
    return m_players();
}

TurnState* Game::state() const
{
    return m_state.get();
}

Bank& Game::bank()
{
    return m_bank;
}