#include "gamelogic.h"

#include <game/game.h>
#include <game/turn/endstate.h>
#include <game/turn/idlestate.h>
#include <game/turn/jailstate.h>
#include <game/turn/movestate.h>
#include <utils/exception.h>

#include <iostream>

namespace
{
const int jailPosition = 10;
const int goToJailPosition = 30;
const int gameEndField = 40;
}

GameLogic::GameLogic(Game* game, StartState* state)
    : m_game(game)
    , m_state(state)
{
}

void GameLogic::movePlayer(int distance, bool canRollAgain, int rollCount)
{
    //auto& player = m_state->player();
    //player.move(distance);
    //emit m_game->onPlayerMove(player.name(), distance);

    //// handle game end
    //if (player.position() >= gameEndField)
    //{
    //    m_game->stateChange<EndState>(m_game);
    //    return;
    //}

    //// handle go to jail field
    //if (player.position() == goToJailPosition)
    //{
    //    goToJail();
    //    return;
    //}

    //if (!canRollAgain)
    //{
    //    m_state->stateChange<IdleState>();
    //}
    //else
    //{
    //    m_state->stateChange<MoveState>(rollCount);
    //}
}

void GameLogic::goToJail()
{
    //auto& player = m_state->player();

    //player.jail();

    //auto distance = jailPosition - player.position();
    //player.move(distance);
    //emit m_game->onPlayerMove(player.name(), distance);
    //emit m_game->onEnterJail(player.name());

    //end();
}

Dices GameLogic::roll()
{
    //auto d = m_state->watson().roll();
    //emit m_game->onRollDice(m_state->player().name(), d.first, d.second);
    return {};
}

void GameLogic::idle()
{
    //m_state->stateChange<IdleState>();
}

void GameLogic::end()
{
	//nextPlayer();
	//prepareTurnState();
}

void GameLogic::nextPlayer()
{
    //m_state->players().next();
    //m_state->player().nextTurn();
    //emit m_game->onTurnChange(m_state->player().name());
}

void GameLogic::prepareTurnState()
{
    //if (m_state->player().inJail())
    //{
    //    m_state->stateChange<JailState>();
    //}
    //else
    //{
    //    m_state->stateChange<MoveState>();
    //}
}
