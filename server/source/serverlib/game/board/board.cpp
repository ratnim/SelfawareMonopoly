#include "board.h"

#include <QJsonArray>
#include <QJsonObject>

Board::Board(std::vector<std::unique_ptr<Field>> fields)
    : m_fields(std::move(fields))
{
}

size_t Board::size() const
{
    return m_fields.size();
}

QJsonObject Board::description() const
{
    QJsonArray fields;
    for (const auto& field : m_fields)
    {
        fields.append(field->description());
    }

    return {
        { "fields", fields }
    };
}

Field* Board::operator[](size_t index)
{
    return m_fields[index].get();
}

int Board::targetForMove(int position, int distance)
{
	if (size() == 0)
	{
        return 0;
	}

	// 2 * size() prefents from wrong index on moving backwards over 0
	return static_cast<int>((position + distance + 2 * size()) % size());
}