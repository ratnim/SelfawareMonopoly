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

GameLogic::GameLogic(Game* game, RunState* state)
    : m_game(game)
    , m_state(state)
    , m_players(state->players())
    , m_watson(state->watson())
{
}

void GameLogic::movePlayer(int distance, bool canRollAgain, int rollCount)
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
        m_state->stateChange<FreeState>();
    }
    else
    {
        m_state->stateChange<RollState>(rollCount);
    }
}

void GameLogic::goToJail()
{
    auto distance = jailPosition - m_players().position;
    m_players().position = jailPosition;
    emit m_game->onPlayerMove(m_players().name, distance);
    emit m_game->onEnterJail(m_players().name);

    m_players().jailTurns = 3;

    end();
}

Dices GameLogic::roll()
{
    auto d = m_watson.roll();
    emit m_game->onRollDice(m_players().name, d.first, d.second);
    return d;
}

void GameLogic::free()
{
    m_state->stateChange<FreeState>();
}

void GameLogic::end()
{
    m_players.next();
    emit m_game->onTurnChange(m_players().name);

    --m_players().jailTurns;
    if (m_players().jailTurns)
    {
        m_state->stateChange<JailState>();
    }
    else
    {
        m_state->stateChange<RollState>();
    }
}
