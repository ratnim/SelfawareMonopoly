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

void JailState::requestRollDice(const QString& playerName)
{
    ensurePlayersTurn(playerName);
    auto& player = m_game->currentPlayer();

    Dices dices = m_game->doCurrentPlayerRollDices();

    if (dices.isDouble())
    {
        player.leaveJail();
        m_game->doCurrentPlayerMove(dices.sum());
	}
	else
	{
        changeToDefaultState();
	}
}

void JailState::requestPossibleRequests(const QString& playerName)
{
    QJsonArray requests;

    if (playersTurn(playerName))
    {
        requests.append(PossibleRequest::rollDice().toJson());
    }

    emit m_game->onPossibleRequests(playerName, requests);
}
