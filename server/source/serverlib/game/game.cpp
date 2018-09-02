#include "game.h"

#include <game/turn/initstate.h>

Game::Game(std::vector<std::unique_ptr<Field>> fields)
    : m_board(std::move(fields))
    , m_players({})
{
    connect(&m_bank, &Bank::onMoneyChange, this, &Game::onMoneyChange);
    connect(&m_board, &Board::onPropertyChange, this, &Game::onPropertyChange);

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

void Game::requestBuyField(const QString& playerName, bool buy)
{
    m_state->requestBuyField(playerName, buy);
}

void Game::requestBuyHouse(const QString& playerName, int fieldId, bool buy)
{
    m_state->requestBuyHouse(playerName, fieldId, buy);
}

void Game::requestChangeHouses(const QString& playerName, const std::vector<std::pair<int,int>>& newLevels)
{
    m_state->requestChangeHouses(playerName, newLevels);
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

void Game::doCurrentPlayerGoToJail()
{
    currentPlayer().canRoll(false);
    currentPlayer().moveTo(m_board.jailIndex());
    emit onPlayerMove(currentPlayer().name(), m_board.jailIndex(), "jump");
    currentPlayer().jail();

    m_state->changeToDefaultState();
}

void Game::doCurrentPlayerMove(int distance)
{
    auto& name = currentPlayer().name();
    auto startPosition = currentPlayer().position();

	for (int step = 1; step <= distance; ++step)
	{
        auto stepTarget = m_board.targetForMove(startPosition, step);
        m_board[stepTarget]->passBy(name, this);
	}

    auto target = m_board.targetForMove(startPosition, distance);
    currentPlayer().moveTo(target);
    emit onPlayerMove(name, target, "forward");

    if (!m_board[target]->moveOn(name, this))
    {
        m_state->changeToDefaultState();
    }
}

void Game::doCurrentPlayerBuyField()
{
    auto propertyId = currentPlayer().position();
    auto price = m_board.fieldPrice(propertyId);
    m_bank.takeMoney(currentPlayer().name(), price);
    m_board.changeOwner(propertyId, currentPlayer().name());
}

void Game::doCurrentPlayerBuyHouse(int fieldID, bool buy)
{
    auto buyPrice = m_board.housePrice(fieldID);
    auto sellPrice = buyPrice / 2;

    m_board.ensureFullGroupOwnership(currentPlayer().name(), fieldID);

    if (buy)
    {
        if (m_bank.balance(currentPlayer().name()) < buyPrice)
        { // throw exception indirectly
            m_bank.takeMoney(currentPlayer().name(), buyPrice);
        }
        m_board.buildHouse(fieldID);
        m_bank.takeMoney(currentPlayer().name(), buyPrice);
    }
    else
    {
        m_board.removeHouse(fieldID);
        m_bank.giveMoney(currentPlayer().name(), sellPrice);
    }
}

void Game::doCurrentPlayerChangeHouses(const std::vector<std::pair<int,int>>& newLevels)
{
    auto cashflow = m_board.checkHouseChangePrice(currentPlayer().name(), newLevels);

    if (cashflow > 0) // player has to pay
    {
        m_bank.takeMoney(currentPlayer().name(), cashflow);
    }
    if (cashflow < 0) // player gets money back
    {
        m_bank.giveMoney(currentPlayer().name(), -cashflow);
    }

    m_board.changeConstructionLevels(newLevels);
}

void Game::doCurrentPlayerEarnMoney(int amount)
{
    m_bank.giveMoney(currentPlayer().name(), amount);
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

Board& Game::board()
{
    return m_board;
}
