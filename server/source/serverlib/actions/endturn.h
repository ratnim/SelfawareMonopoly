#pragma once

#include <actions/gameaction.h>
#include <game/game.h>

class EndTurn : public GameAction
{
public:
    EndTurn(const QString& playerName, Game& game);

    void handle(const QJsonValue& body) override;

protected:
    void changeTurn(const QString& movingPlayer);
    QString answer(const QString& movingPlayer);
};
