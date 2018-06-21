#pragma once

#include <QString>

struct Player
{
    Player(const QString& playerName);

    const QString name;
    int jailTurns = 0;
    int position = 0;
};