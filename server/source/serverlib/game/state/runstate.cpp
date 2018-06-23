#include "runstate.h"

#include <game/game.h>
#include <game/state/active/rollstate.h>
#include <utils/exception.h>

RunState::RunState(GameState* old, Game* game, std::vector<Player> order)
    : m_player(std::move(order))
    , m_logic(game, this, m_player)
{
    emit game->onGameStart();
    emit game->onTurnChange(m_player().name);

    stateChange<RollState>(&m_logic);
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
