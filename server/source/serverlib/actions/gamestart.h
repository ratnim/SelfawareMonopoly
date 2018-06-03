#pragma once

#include <actions/gameaction.h>
#include <game/game.h>

class GameStart : public GameAction
{
public:
    GameStart(const QString& playerName, Game& game);

    void handle(const QJsonValue& body) override;

protected:
    void gameStart();
    QString answer();
};
