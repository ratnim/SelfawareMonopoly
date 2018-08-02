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
{
}

void GameLogic::movePlayer(int distance, bool canRollAgain, int rollCount)
{
    auto& player = m_state->player();
    player.position += distance;
    emit m_game->onPlayerMove(player.name, distance);

    // handle game end
    if (player.position >= gameEndField)
    {
        m_game->stateChange<EndState>(m_game);
        return;
    }

    // handle go to jail field
    if (player.position == goToJailPosition)
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
    auto& player = m_state->player();
    auto distance = jailPosition - player.position;
    player.position = jailPosition;
    emit m_game->onPlayerMove(player.name, distance);
    emit m_game->onEnterJail(player.name);

    player.jailTurns = 3;

    end();
}

Dices GameLogic::roll()
{
    auto d = m_state->watson().roll();
    emit m_game->onRollDice(m_state->player().name, d.first, d.second);
    return d;
}

void GameLogic::free()
{
    m_state->stateChange<FreeState>();
}

void GameLogic::end()
{
    m_state->players().next();
    auto& player = m_state->player();
    emit m_game->onTurnChange(player.name);

    --player.jailTurns;
    if (player.jailTurns)
    {
        m_state->stateChange<JailState>();
    }
    else
    {
        m_state->stateChange<RollState>();
    }
}
