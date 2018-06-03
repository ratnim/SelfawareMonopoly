#pragma once

#include <actions/action.h>

class CreateGame : public Action
{
public:
    CreateGame(const QString &playerName);

    void handle(const QJsonValue& body) override;

protected:
    QString answer(int gameId);

    const QString& m_playerName;
};
