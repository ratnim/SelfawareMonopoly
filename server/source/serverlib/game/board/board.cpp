#include "board.h"

size_t Board::size() const
{
    return m_fields.size();
}

Field* Board::operator[](size_t index)
{
    return &m_fields[index];
}