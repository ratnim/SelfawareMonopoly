#include "game.h"

#include <game/turn/initstate.h>

Game::Game(std::vector<std::unique_ptr<Field>> fields)
    : m_board(std::move(fields))
    , m_players({})
    , m_watson(this)
    , m_eventStack(CardStack::chanceStack())
    , m_societyStack(CardStack::societyStack())
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

void Game::requestChangeHouses(const QString& playerName, const std::vector<std::pair<int, int>>& newLevels)
{
    m_state->requestChangeHouses(playerName, newLevels);
}

void Game::requestPossibleRequests(const QString& playerName)
{
    m_state->requestPossibleRequests(playerName);
}

void Game::requestPayDebt(const QString& debtor, const QString& beneficiary)
{
    m_state->requestPayDebt(debtor, beneficiary);
}

Dices Game::doCurrentPlayerRollDices()
{
    currentPlayer().rolled();
    Dices dices;
    if (m_watson.diceAreManipulated(currentPlayer().name()))
    {
        dices = m_watson.getManipulatedDices(currentPlayer().name());
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

    if (!m_board[target]->moveOn(name, this, distance))
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

void Game::doCurrentPlayerChangeHouses(const std::vector<std::pair<int, int>>& newLevels)
{
    auto cashflow = m_board.calculateConstructionPrice(currentPlayer().name(), newLevels);

    if (cashflow > 0)  // player has to pay
    {
        auto toPay = cashflow;
        auto watsonMoney = m_watson.availableMoneyForCoins(currentPlayer().name());
		if (watsonMoney > cashflow)
		{
            m_watson.doUseCoinsForMoney(currentPlayer().name(), cashflow);
            toPay = 0;
		}
		else
		{
            m_watson.doUseCoinsForMoney(currentPlayer().name(), watsonMoney);
            toPay = cashflow - watsonMoney;
		}

		m_bank.takeMoney(currentPlayer().name(), toPay);
    }
    if (cashflow < 0)  // player gets money back
    {
        m_bank.giveMoney(currentPlayer().name(), -cashflow);	
    }

    m_board.changeConstructionLevels(currentPlayer().name(), newLevels);
}

void Game::doCurrentPlayerEarnMoney(int amount)
{
    m_bank.giveMoney(currentPlayer().name(), amount);
}

void Game::doTransferMoney(const QString& sender, const QString& reciever, int amount)
{
    m_bank.transferMoney(sender, reciever, amount);
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

CardStack& Game::eventStack()
{
    return m_eventStack;
}

CardStack& Game::societyStack()
{
    return m_societyStack;
}

Watson& Game::watson()
{
    return m_watson;
}
