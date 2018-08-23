#include "runstage.h"

#include <game/game.h>
#include <game/turn/rollstate.h>
#include <utils/exception.h>

RunStage::RunStage(Game* game, std::vector<Player> players)
    : m_players(std::move(players))
    , m_logic(game, this)
{
    emit game->onGameStart();
    emit game->onTurnChange(m_players().name());

    stateChange<RollState>(&m_logic);
}

Player& RunStage::player()
{
    return m_players();
}

RingBuffer<Player>& RunStage::players()
{
    return m_players;
}

Watson& RunStage::watson()
{
    return m_watson;
}

void RunStage::rollDice(const QString& playerName)
{
    checkPlayer(playerName);
    m_state->rollDice();
}

void RunStage::endTurn(const QString& playerName)
{
    checkPlayer(playerName);
    m_state->endTurn();
}

void RunStage::checkPlayer(const QString& playerName)
{
    if (m_players().name() != playerName)
    {
        throw Exception("Not your turn.");
    }
}
