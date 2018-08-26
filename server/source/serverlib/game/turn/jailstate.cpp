#include "jailstate.h"

#include <QJsonArray>

#include <game/dices.h>
#include <game/game.h>
#include <game/turn/idlestate.h>
#include <game/turn/possiblerequest.h>

JailState::JailState(TurnState* state)
    : TurnState(*state)
{
    broadcastPossibleRequests();
}

void JailState::rollDice(const QString& playerName)
{
    ensurePlayersTurn(playerName);
    auto& player = m_game->currentPlayer();

    Dices dices = m_game->currentPlayerRollDices();
    m_game->onRollDice(playerName, dices.first, dices.second);

    if (dices.isDouble())
    {
        player.move(dices.sum());
        emit m_game->onPlayerMove(playerName, dices.sum());
        player.leaveJail();
	}
	
	m_game->stateChange<IdleState>();
}

void JailState::possibleRequests(const QString& playerName)
{
    QJsonArray requests;

    if (playersTurn(playerName))
    {
        requests.append(PossibleRequest::rollDice().toJson());
    }

    emit m_game->onPossibleRequests(playerName, requests);
}
