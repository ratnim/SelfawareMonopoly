#include "turnstate.h"

#include <QJsonObject>

#include <game/game.h>
#include <game/stages/runstage.h>
#include <game/turn/jailstate.h>
#include <game/turn/rollstate.h>
#include <utils/exception.h>

TurnState::TurnState(GameLogic* logic)
    : m_logic(logic)
{
}

void TurnState::startGame()
{
    InvalidRequest();
}

void TurnState::playerJoin(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::playerReady(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::rollDice(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::endTurn(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::possibleRequests(const QString& playerName)
{
    InvalidRequest();
}

void TurnState::InvalidRequest()
{
    throw Exception("You are not allowed to perform this action.", Error::InvalidRequest);
}

QJsonObject TurnState::createPossibleRequest(const QString& requestName) const
{
    QJsonObject request;
    request["request"] = requestName;
    request["data"] = QJsonObject{};
    return request;
}
