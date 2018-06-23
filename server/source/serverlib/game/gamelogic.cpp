#include "gamelogic.h"

#include <game/state/turn/freestate.h>
#include <game/state/turn/jailstate.h>
#include <game/state/turn/rollstate.h>
#include <game/state/endstate.h>
#include <game/state/runstate.h>
#include <utils/exception.h>

namespace
{
const int jailPosition = 10;
const int goToJailPosition = 30;
const int gameEndField = 40;
}

GameLogic::GameLogic(Game* game, RunState* state, RingBuffer<Player>& player)
    : m_game(game)
    , m_state(state)
    , m_player(player)
{
}

void GameLogic::movePlayer(int distance, bool canRollAgain, int rollCount)
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
        m_state->stateChange<FreeState>();
    }
    else
    {
        m_state->stateChange<RollState>(rollCount);
    }
}

void GameLogic::goToJail()
{
    auto distance = jailPosition - m_player().position;
    m_player().position = jailPosition;
    emit m_game->onPlayerMove(m_player().name, distance);
    emit m_game->onEnterJail(m_player().name);

    m_player().jailTurns = 3;

    end();
}

Dices GameLogic::roll()
{
    // TODO get dices from watson
    Dices d;
    emit m_game->onRollDice(d.first, d.second);
    return d;
}

void GameLogic::free()
{
    m_state->stateChange<FreeState>();
}

void GameLogic::end()
{
    m_player.next();
    emit m_game->onTurnChange(m_player().name);

    --m_player().jailTurns;
    if (m_player().jailTurns)
    {
        m_state->stateChange<JailState>();
    }
    else
    {
        m_state->stateChange<RollState>();
    }
}
