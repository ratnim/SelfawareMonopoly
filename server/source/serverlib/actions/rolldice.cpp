#include "rolldice.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

RollDice::RollDice(const QString& playerName, Game& game)
    : GameAction(playerName, game)
{
    connect(&game, &Game::onRollDice, this, &RollDice::rollDice);
}

void RollDice::handle(const QJsonValue& body)
{
    m_game.rollDice(m_playerName);
}

void RollDice::rollDice(int d1, int d2)
{
    emit send(answer(d1, d2));
}

QString RollDice::answer(int d1, int d2)
{
    QJsonObject answer({ { "name", "roll_dice" } });
    answer["data"] = QJsonArray({d1, d2});

    return QJsonDocument(answer).toJson();
}
