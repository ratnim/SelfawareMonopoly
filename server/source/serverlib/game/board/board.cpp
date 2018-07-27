#include "board.h"

Board::Board(std::vector<std::unique_ptr<Field>> fields)
	: m_fields(std::move(fields))
{
}

size_t Board::size() const
{
    return m_fields.size();
}

Field* Board::operator[](size_t index)
{
    return m_fields[index].get();
}