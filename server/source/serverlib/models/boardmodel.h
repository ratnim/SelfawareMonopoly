#pragma once

#include <game/board/board.h>
#include <utils/staticstorage.h>

class BoardModel : public StaticStorage<BoardModel>
{
public:
    Board new_board() const;

};