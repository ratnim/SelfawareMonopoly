#pragma once

#include <actions/gameaction.h>
#include <game/game.h>

class JoinGame : public GameAction
{
public:
    JoinGame(const QString& playerName, Game& game);

    void handle(const QJsonValue& body) override;

protected:
    void playerJoin(const QString& playerName);
    QString answer(const QString& playerName);
};
