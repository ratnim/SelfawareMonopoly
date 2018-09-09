#include "station.h"

#include <game/board/board.h>

Station::Station(const QString& name, int group, int price, int baseRent)
    : OwnableField(name, FieldType::station, price)
    , m_group(group)
    , m_baseRent(baseRent)
{
}

int Station::group() const
{
    return m_group;
}

int Station::rent(const Board & board) const
{
    int rent = m_baseRent;

    for (size_t i = 0; i < board.size(); ++i)
    {
        auto field = board[i];

        if (auto station = dynamic_cast<const Station*>(field))
        {
            if (station == this)
                continue;

            if (m_group == station->group()
             && m_owner == station->owner())
                rent *= 2;
        }
    }

    return rent;
}

QJsonObject Station::description()
{
    auto description = OwnableField::description();
    description["group"] = m_group;
    description["base_rent"] = m_baseRent;
    return description;
}
