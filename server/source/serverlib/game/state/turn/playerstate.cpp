#include "turnstate.h"

#include <game/game.h>
#include <game/state/runstate.h>
#include <game/state/turn/jailstate.h>
#include <game/state/turn/rollstate.h>
#include <utils/exception.h>

TurnState::TurnState(Game* game, RunState* state, RingBuffer<Player>& player)
    : m_game(game)
    , m_state(state)
    , m_players(player)
{
}

void TurnState::rollDice()
{
    InvalidRequest();
}

void TurnState::endTurn()
{
    InvalidRequest();
}

void TurnState::end()
{
    m_players.next();
    emit m_game->onTurnChange(m_players().name);

    --m_players().jailTurns;
    if (m_players().jailTurns)
    {
        m_state->stateChange<JailState>(this);
    }
    else
    {
        m_state->stateChange<RollState>(this);
    }
}

void TurnState::InvalidRequest()
{
    throw Exception("You are not allowed to perform this action.", error::InvalidRequest);
}
