#pragma once

#include <QString>

#include <vector>

struct GameState
{
    int32_t turn = -1;
    std::vector<QString> playerNames;
};
