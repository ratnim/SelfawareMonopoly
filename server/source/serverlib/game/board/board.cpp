#include "board.h"

#include <QJsonArray>
#include <QJsonObject>

#include <game/board/street.h>

#include <utils/exception.h>

Board::Board(std::vector<std::unique_ptr<Field>> fields)
    : m_fields(std::move(fields))
    , m_jailIndex(0)
{
    initializeGroups();
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

int Board::distanceToNextField(int position, FieldType type) const
{
	for (int distance = 1; distance <= size(); ++distance)
	{
        auto target = (position + distance) % size();
		if (m_fields[target]->type() == type)
		{
            return distance;
		}
	}
    return 0;
}

int Board::jailIndex() const
{
    return m_jailIndex;
}

void Board::initializeGroups()
{
	for (int id = 0; id < m_fields.size(); ++id)
	{
        auto street = dynamic_cast<Street*>(m_fields[id].get());
		if (street == nullptr)
		{
            continue;
		}

		if (m_groups.size() <= street->group())
		{
            m_groups.resize(street->group() + 1);
		}

		m_groups[street->group()].push_back(id);
	}
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

std::vector<int> Board::ownedGroups(const QString& playerName)
{
    std::vector<int> ownedGroups;
    for (int groupId = 0; groupId < m_groups.size(); ++groupId)
    {
        if (isGroupOwner(playerName, groupId))
        {
            ownedGroups.push_back(groupId);
        }
    }
    return ownedGroups;
}

bool Board::isGroupOwner(const QString& playerName, int groupId)
{
    if (groupId >= m_groups.size() || m_groups[groupId].size() == 0)
    {
        return false;
    }

    for (auto id : m_groups[groupId])
    {
        auto street = dynamic_cast<Street*>(m_fields[id].get());
        if (street == nullptr || street->owner() != playerName)
        {
            return false;
        }
    }

    return true;
}

void Board::changeOwner(int id, const QString& owner)
{
    auto street = dynamic_cast<Street*>(m_fields[id].get());
    if (street == nullptr)
    {
        throw Exception("Field is not a street.", Error::InvalidRequest);
    }
    street->changeOwner(owner);

    emit onPropertyChange(id, street->owner(), street->constructionLevel());
}

void Board::changeConstructionLevels(const QString& owner, const std::vector<std::pair<int, int>>& newLevels)
{
    validateConstructionLevels(owner, newLevels);

    for (const auto[id, level] : newLevels)
    {
        changeConstructionLevel(id, ConstructionLevel(level));
    }
}

void Board::changeConstructionLevel(int id, ConstructionLevel level)
{
    auto street = dynamic_cast<Street*>(m_fields[id].get());
    if (street == nullptr)
    {
        throw Exception("Field is not a street.", Error::InvalidRequest);
    }

    if (level != street->constructionLevel())
    {
        street->changeConstructionLevel(ConstructionLevel(level));

        emit onPropertyChange(id, street->owner(), level);
    }
}

int Board::fieldPrice(int id)
{
    auto street = dynamic_cast<Street*>(m_fields[id].get());
    if (street == nullptr)
    {
        throw Exception("Field is not a street.", Error::InvalidRequest);
    }
    return street->price();
}

int Board::housePrice(int id)
{
    auto street = dynamic_cast<Street*>(m_fields[id].get());
    if (street == nullptr)
    {
        throw Exception("Field is not a street.", Error::InvalidRequest);
    }
    return street->housePrice();
}

int Board::calculateConstructionPrice(const QString& owner, const std::vector<std::pair<int, int>>& newLevels)
{
    validateConstructionLevels(owner, newLevels);

    int fullPrice = 0;
    int fullReturn = 0;

    for (const auto[id, level] : newLevels)
    {
        auto street = dynamic_cast<Street*>(m_fields[id].get());

        if (street->constructionLevel() < level)
        {
            fullPrice += street->housePrice() * (level - street->constructionLevel());
        }

        if (street->constructionLevel() > level)
        {
            fullReturn += street->housePrice() * (street->constructionLevel() - level) / 2;
        }
    }

    return fullPrice - fullReturn;
}

void Board::validateConstructionLevels(const QString& owner, const std::vector<std::pair<int, int>>& levels)
{
    uint8_t levelValidation = 0b00111111;  // TODO: More dynamic: one '1' bit per building level
    int group = -1;

    for (const auto[id, level] : levels)
    {
        if (level < ConstructionLevel::BASE || level > ConstructionLevel::HOTEL)
        {
            throw Exception("Invalid construction level", Error::InvalidRequest);
        }

        auto street = dynamic_cast<Street*>(m_fields[id].get());

        if (street == nullptr)
        {
            throw Exception("Field is not a street.", Error::InvalidRequest);
        }

        if (street->owner() != owner)
        {
            throw Exception("Player does not own street.", Error::InvalidRequest);
        }

        if (group == -1)
        {
            group = street->group();
        }

        if (street->group() != group)
        {
            throw Exception("Not all streets belong to the same group.", Error::InvalidRequest);
        }

        levelValidation &= 0b11 << level;
    }

    if (levelValidation == 0)
    {
        throw Exception("Construciton levels differ too much.", Error::InvalidRequest);
    }
}
