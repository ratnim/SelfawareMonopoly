#include "watson.h"

#include <game/dices.h>
#include <game/game.h>

#include <utils/exception.h>

Watson::Watson(Game* game)
    : m_game(game)
{
}

void Watson::requestAddClick(const QString& playerName, const QString& addName)
{
    if (!currentPlayerRequest(playerName) && !diceAreManipulated(m_game->currentPlayer().name()))
    {
        doHarmCurrentPlayer();
    }
}

void Watson::requestScannedGMailAccount(const QString& playerName, Dices dices)
{
    doManipulateNextRoll(playerName, dices);
}

void Watson::requestGatherWatsonCoin(const QString& playerName, int amount, const QString& source)
{
    doAddWatsonCoins(playerName, amount);
}

void Watson::doManipulateNextRoll(const QString& playerName, int x, int y)
{
    doManipulateNextRoll(playerName, { x, y });
}

void Watson::doManipulateNextRoll(const QString& playerName, Dices dices)
{
    m_manipulatedDices.erase(playerName);
    m_manipulatedDices.emplace(playerName, dices);
}

void Watson::doHarmCurrentPlayer()
{
    auto start = m_game->currentPlayer().position();
    auto distance = m_game->board().distanceToNextField(start, FieldType::tax);

    try
    {
        Dices dices{ distance };
        doManipulateNextRoll(m_game->currentPlayer().name(), dices);
    }
    catch (Exception)
    {
    };
}

void Watson::doAddWatsonCoins(const QString& playerName, int coins)
{
    createCoinAccountIfNotExisting(playerName);
    m_coins[playerName] += coins;
}

void Watson::doUseCoinsForMoney(const QString& playerName, int money)
{
    createCoinAccountIfNotExisting(playerName);

    if (money > availableMoneyForCoins(playerName))
    {
        throw Exception("Not enough coins available.", Error::InsufficientCoins);
    }

	m_coins[playerName] -= coinsForMoneyNeeded(money);
}

bool Watson::diceAreManipulated(const QString& playerName) const
{
    auto it = m_manipulatedDices.find(playerName);
    bool manipulated = it != m_manipulatedDices.end();
    return manipulated;
}

int Watson::availableMoneyForCoins(const QString& playerName)
{
    createCoinAccountIfNotExisting(playerName);
    return coinsToMoney(m_coins[playerName]);
}

bool Watson::currentPlayerRequest(const QString& playerName) const
{
    return m_game->currentPlayer().name() == playerName;
}

Dices Watson::getManipulatedDices(const QString& playerName)
{
    auto dices = m_manipulatedDices.at(playerName);
    m_manipulatedDices.erase(playerName);
    return dices;
}

int Watson::coinsToMoney(int coins)
{
    return coins * course;
}

int Watson::coinsForMoneyNeeded(int money)
{
    return std::ceil(money / float(course));
}

void Watson::createCoinAccountIfNotExisting(const QString& playerName)
{
    auto it = m_coins.find(playerName);
    if (it == m_coins.end())
    {
        m_coins.emplace(playerName, 0);
    }
}
