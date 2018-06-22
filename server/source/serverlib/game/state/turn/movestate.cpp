#include "movestate.h"

#include <game/game.h>
#include <game/state/turn/freestate.h>
#include <game/state/turn/rollstate.h>
#include <game/state/endstate.h>
#include <game/state/runstate.h>

namespace
{
const int jailPosition = 10;
const int goToJailPosition = 30;
const int gameEndField = 40;
}

MoveState::MoveState(TurnState* state)
    : TurnState(*state)
{
}

void MoveState::movePlayer(int distance, bool canRollAgain, int rollCount)
{
    m_players().position += distance;
    emit m_game->onPlayerMove(m_players().name, distance);

    // handle game end
    if (m_players().position >= gameEndField)
    {
        m_game->stateChange<EndState>(m_game);
        return;
    }

    // handle go to jail field
    if (m_players().position == goToJailPosition)
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

void MoveState::goToJail()
{
    auto distance = jailPosition - m_players().position;
    m_players().position = jailPosition;
    emit m_game->onPlayerMove(m_players().name, distance);
    emit m_game->onEnterJail(m_players().name);

    m_players().jailTurns = 3;

    end();
}

Dices MoveState::roll()
{
    // TODO get dices from watson
    Dices d;
    emit m_game->onRollDice(d.first, d.second);
    return d;
}
