#include "game.h"

#include <game/state/initstate.h>

Game::Game()
{
    stateChange<InitState>(this);
}

void Game::join(const QString& playerName)
{
    m_state->join(playerName);
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
