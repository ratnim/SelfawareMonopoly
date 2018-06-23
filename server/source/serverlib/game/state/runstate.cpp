#include "runstate.h"

#include <game/game.h>
#include <game/state/turn/rollstate.h>
#include <utils/exception.h>

RunState::RunState(Game* game, std::vector<Player> players)
    : m_players(std::move(players))
    , m_logic(game, this, m_players)
{
    emit game->onGameStart();
    emit game->onTurnChange(m_players().name);

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
    if (m_players().name != playerName)
    {
        throw Exception("Not your turn.");
    }
}
