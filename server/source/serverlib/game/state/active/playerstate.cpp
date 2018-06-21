#include "playerstate.h"

#include <game/game.h>
#include <game/state/runstate.h>
#include <game/state/active/jailstate.h>
#include <game/state/active/rollstate.h>
#include <utils/exception.h>

PlayerState::PlayerState(Game* game, RunState* state, RingBuffer<Player>& player)
    : m_game(game)
    , m_state(state)
    , m_player(player)
{
}

void PlayerState::rollDice()
{
    InvalidRequest();
}

void PlayerState::endTurn()
{
    InvalidRequest();
}

void PlayerState::end()
{
    m_player.next();
    emit m_game->onTurnChange(m_player().name);

    --m_player().jailTurns;
    if (m_player().jailTurns)
    {
        m_state->stateChange<JailState>(this);
    }
    else
    {
        m_state->stateChange<RollState>(this);
    }
}

void PlayerState::InvalidRequest()
{
    throw Exception("You are not allowed to perform this action.", error::InvalidRequest);
}
