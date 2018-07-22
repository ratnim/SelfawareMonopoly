#pragma once

#include <vector>

#include <game/board/field.h>

class Board
{
public:
    size_t size() const;

    Field* operator[](size_t index);
protected:
    std::vector<Field> m_fields;
};
