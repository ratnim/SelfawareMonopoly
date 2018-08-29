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
    m_state->requestPlayerReady(playerName);
}

void Game::requestGameStart()
{
    m_state->requestGameStart();
}

void Game::requestRollDice(const QString& playerName)
{
    m_state->requestRollDice(playerName);
}

void Game::requestEndTurn(const QString& playerName)
{
    m_state->requestEndTurn(playerName);
}

void Game::requestPossibleRequests(const QString& playerName)
{
    m_state->requestPossibleRequests(playerName);
}

Dices Game::doCurrentPlayerRollDices()
{
    currentPlayer().rolled();
    Dices dices;
    if (!watson_next_rolls.empty())
    {
        dices = watson_next_rolls.front();
        watson_next_rolls.pop();
    }

	emit onRollDice(currentPlayer().name(), dices.first, dices.second);
	return dices;
}

void Game::doJailCurrentPlayer()
{
    currentPlayer().canRoll(false);
    currentPlayer().moveTo(JAIL_POSITION);
    emit onPlayerMove(currentPlayer().name(), JAIL_POSITION, "jump");
    currentPlayer().jail();

	m_state->changeToDefaultState();
}

void Game::doMoveCurrentPlayer(int distance)
{
    auto target = m_board.targetForMove(currentPlayer().position(), distance);
    currentPlayer().moveTo(target);
	emit onPlayerMove(currentPlayer().name(), target, "forward");

	
	// special position
    // buy
    // rent
    // tax
    // what ever
    if (target == GO_TO_JAIL_POSITION)
    {
    	doJailCurrentPlayer();
    }
	else
	{
		m_state->changeToDefaultState();
	}
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