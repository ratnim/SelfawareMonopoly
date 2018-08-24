#include "startstate.h"

#include <game/game.h>

#include <game/turn/rollstate.h>

StartState::StartState(TurnState* state, std::vector<Player> players)
    : TurnState(*state)
{
    m_game->players() = RingBuffer<Player>(players);
    emit m_game->onGameStart();
    emit m_game->onTurnChange(m_game->currentPlayer().name());

	m_game->stateChange<RollState>(this);
}
