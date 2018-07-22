#pragma once

#include <QString>

struct Player
{
    bool ready = false;
    bool inJail = false;
    int jailTurns = 0;
    int position = 0;
};