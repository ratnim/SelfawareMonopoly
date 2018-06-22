#include "runstate.h"

#include <game/game.h>
#include <game/state/active/rollstate.h>
#include <utils/exception.h>

RunState::RunState(Game* game, std::vector<Player> order)
    : m_game(game)
    , m_player(std::move(order))
{
    emit m_game->onGameStart();
    emit m_game->onTurnChange(m_player().name);

    PlayerState initialState(game, this, m_player);
    stateChange<RollState>(&initialState);
}

void RunState::rollDice(const QString& playerName)
{
    checkPlayer(playerName);
    m_state->rollDice();
}

void RunState::endTurn(const QString& playerName)
{
    checkPlayer(playerName);
    m_state->endTurn();
}

void RunState::checkPlayer(const QString& playerName)
{
    if (m_player().name != playerName)
    {
        throw Exception("Not your turn.");
    }
}
