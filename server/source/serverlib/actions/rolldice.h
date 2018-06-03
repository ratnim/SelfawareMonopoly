#pragma once

#include <actions/gameaction.h>
#include <game/game.h>

class RollDice : public GameAction
{
public:
    RollDice(const QString& playerName, Game& game);

    void handle(const QJsonValue& body) override;

protected:
    void rollDice(int d1, int d2);
    QString answer(int d1, int d2);
};
