#include "endturn.h"

#include <QJsonDocument>
#include <QJsonObject>

EndTurn::EndTurn(const QString& playerName, Game& game)
    : GameAction(playerName, game)
{
    connect(&game, &Game::onTurnChange, this, &EndTurn::changeTurn);
}

void EndTurn::handle(const QJsonValue& body)
{
    m_game.endTurn(m_playerName);
}

void EndTurn::changeTurn(const QString& movingPlayer)
{
    emit send(answer(movingPlayer));
}

QString EndTurn::answer(const QString& movingPlayer)
{
    QJsonObject answer({ { "name", "change_turn" } });
    answer["data"] = movingPlayer;

    return QJsonDocument(answer).toJson();
}
