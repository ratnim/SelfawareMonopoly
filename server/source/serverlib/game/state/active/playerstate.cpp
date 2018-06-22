#include "playerstate.h"

#include <game/game.h>
#include <game/state/runstate.h>
#include <game/state/endstate.h>
#include <game/state/active/freestate.h>
#include <game/state/active/jailstate.h>
#include <game/state/active/rollstate.h>
#include <utils/exception.h>

namespace
{
const int jailPosition = 10;
const int goToJailPosition = 30;
const int gameEndField = 40;
}

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

void PlayerState::movePlayer(int distance, bool canRollAgain, int rollCount)
{
    m_player().position += distance;
    emit m_game->onPlayerMove(m_player().name, distance);

    // handle game end
    if (m_player().position >= gameEndField)
    {
        m_game->stateChange<EndState>(m_game);
        return;
    }

    // handle go to jail field
    if (m_player().position == goToJailPosition)
    {
        goToJail();
        return;
    }

    if (!canRollAgain)
    {
        m_state->stateChange<FreeState>(this);
    }
    else
    {
        m_state->stateChange<RollState>(this, rollCount);
    }
}

void PlayerState::goToJail()
{
    auto distance = jailPosition - m_player().position;
    m_player().position = jailPosition;
    emit m_game->onPlayerMove(m_player().name, distance);
    emit m_game->onEnterJail(m_player().name);

    m_player().jailTurns = 3;

    end();
}

Dices PlayerState::roll()
{
    // TODO get dices from watson
    Dices d;
    emit m_game->onRollDice(d.first, d.second);
    return d;
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
