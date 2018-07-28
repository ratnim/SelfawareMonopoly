#include "board.h"

#include <QJsonObject>
#include <QJsonArray>

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
	for(const auto& field : m_fields)
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
