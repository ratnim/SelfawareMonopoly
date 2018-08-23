#pragma once

#include <vector>
#include <memory>

#include <game/board/field.h>

class Board
{
public:
    Board(std::vector<std::unique_ptr<Field>> fields);
    size_t size() const;

	QJsonObject description() const;

    Field* operator[](size_t index);

protected:
    std::vector<std::unique_ptr<Field>> m_fields;
};
