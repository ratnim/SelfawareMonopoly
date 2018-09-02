#include "board.h"

#include <QJsonArray>
#include <QJsonObject>

#include <game/board/street.h>

#include <utils/exception.h>

Board::Board(std::vector<std::unique_ptr<Field>> fields)
    : m_fields(std::move(fields))
    , m_jailIndex(0)
{
    findAndSetJailIndex();
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

int Board::jailIndex() const
{
    return m_jailIndex;
}

void Board::findAndSetJailIndex()
{
	for (int i = 0; i < size(); ++i)
	{
		if (m_fields[i]->type() == FieldType::jail)
		{
            m_jailIndex = i;
            return;
		}
	}
    m_jailIndex = 0;
}

void Board::changeOwner(int id, const QString& owner)
{
    auto street = dynamic_cast<Street*>(m_fields[id].get());
    if (street == nullptr)
    {
        throw Exception("Field is not a street.");
    }
    street->changeOwner(owner);

	emit onPropertyChange(id, street->owner(), street->constructionLevel());
}

void Board::buildHouse(int id)
{
    auto street = dynamic_cast<Street*>(m_fields[id].get());
	if (street == nullptr)
	{
        throw Exception("Field is not a street.");
	}

    const ConstructionLevel level = street->constructionLevel();

    if (level == ConstructionLevel::HOTEL)
    {
        throw Exception("Street already has a hotel.");
    }

    street->changeConstructionLevel(ConstructionLevel(level + 1));

	emit onPropertyChange(id, street->owner(), street->constructionLevel());
}

void Board::removeHouse(int id)
{
    auto street = dynamic_cast<Street*>(m_fields[id].get());
	if (street == nullptr)
	{
        throw Exception("Field is not a street.");
	}

    const ConstructionLevel level = street->constructionLevel();

    if (level == ConstructionLevel::BASE)
    {
        throw Exception("Street already has no houses.");
    }

    street->changeConstructionLevel(ConstructionLevel(level - 1));

	emit onPropertyChange(id, street->owner(), street->constructionLevel());
}

void Board::changeConstructionLevels(const std::vector<std::pair<int,int>>& newLevels)
{
    for (const auto [id, level] : newLevels)
    {
        auto street = dynamic_cast<Street*>(m_fields[id].get());

        if (street == nullptr)
        {
            throw Exception("Field is not a street.");
        }

        street->changeConstructionLevel(ConstructionLevel(level));
    }
}

int Board::fieldPrice(int id)
{
    auto street = dynamic_cast<Street*>(m_fields[id].get());
	if (street == nullptr)
	{
        throw Exception("Field is not a street.");
	}
    return street->price();
}

int Board::housePrice(int id)
{
    auto street = dynamic_cast<Street*>(m_fields[id].get());
	if (street == nullptr)
	{
        throw Exception("Field is not a street.");
	}
    return street->housePrice();
}

int Board::checkHouseChangePrice(const QString& owner, const std::vector<std::pair<int,int>>& newLevels)
{
    int fullPrice = 0;
    int fullReturn = 0;

    uint8_t levelValidation = 0b00111111; // TODO: More dynamic: one '1' bit per building level

    for (const auto [id, level] : newLevels)
    {
        if (level < ConstructionLevel::BASE || level > ConstructionLevel::HOTEL)
        {
            throw Exception("Invalid construction level");
        }

        auto street = dynamic_cast<Street*>(m_fields[id].get());

        if (street == nullptr)
        {
            throw Exception("Field is not a street.");
        }

        if (street->owner() != owner)
        {
            throw Exception("Player does not own street.");
        }

        if (street->constructionLevel() > level)
        {
            fullPrice += street->housePrice() * (level - street->constructionLevel());
        }

        if (street->constructionLevel() < level)
        {
            fullReturn += street->housePrice() * (street->constructionLevel() - level) / 2;
        }

        levelValidation &= 0b11 << level;
    }

    if (levelValidation == 0)
    {
        throw Exception("Construciton levels differ too much.");
    }

    return fullPrice - fullReturn;
}

void Board::ensureFullGroupOwnership(const QString& owner, int id)
{
    auto firstStreet = dynamic_cast<Street*>(m_fields[id].get());
    if (firstStreet == nullptr)
    {
        throw Exception("Field is not a street.");
    }

    const auto checkedGroup = firstStreet->group();

    for (auto& field : m_fields)
    {
        if (auto street = dynamic_cast<Street*>(field.get()))
        {
            if ((street->group() == checkedGroup)
             && (street->owner() != owner))
            {
                throw Exception("Player does not own full group.", Error::InvalidRequest);
            }
        }
    }
}
