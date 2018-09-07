#include "watson.h"

#include <game/game.h>

#include <utils/exception.h>

Watson::Watson(Game* game)
    : m_game(game)
{
}

void Watson::requestAddClick(const QString& playerName, const QString& addName)
{
    if (!currentPlayerRequest(playerName) && !diceAreManipulated())
    {
        doHarmCurrentPlayer();
    }
}

void Watson::doManipulateNextRoll(int x, int y)
{
    doManipulateNextRoll({ x, y });
}

void Watson::doManipulateNextRoll(Dices dices)
{
    clearRolls();
    m_nextRolls.emplace(dices);
}

void Watson::doHarmCurrentPlayer()
{
    auto start = m_game->currentPlayer().position();
    auto distance = m_game->board().distanceToNextField(start, FieldType::tax);

	try
	{
        Dices dices{distance};
        doManipulateNextRoll(dices);
	}
    catch (Exception)
	{
    };
}

bool Watson::diceAreManipulated() const
{
    return !m_nextRolls.empty();
}

bool Watson::currentPlayerRequest(const QString& playerName) const
{
    return m_game->currentPlayer().name() == playerName;
}

Dices Watson::getManipulatedDices()
{
	auto dices = m_nextRolls.front();
    m_nextRolls.pop();
    return dices;
}

void Watson::clearRolls()
{
	while (!m_nextRolls.empty())
	{
        m_nextRolls.pop();
	}
}
