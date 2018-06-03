#pragma once

#include <actions/gameaction.h>
#include <game/game.h>

class PlayerReady : public GameAction
{
public:
    PlayerReady(const QString& playerName, Game& game);

    void handle(const QJsonValue& body) override;

protected:
    void playerReady(const QString& playerName);
    QString answer(const QString& playerName);
};
