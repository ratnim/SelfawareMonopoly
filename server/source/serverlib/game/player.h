#pragma once

#include <QString>

const int BOARD_SIZE = 36;

struct Player
{
    bool ready = false;
    bool inJail = false;
    bool canRoll = true;

	int position = 0;
	int rolled = 0;
};