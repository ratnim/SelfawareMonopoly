#include "utility.h"

#include <game/board/board.h>

Utility::Utility(const QString& name, int group, int price, std::vector<int> rents)
    : OwnableField(name, FieldType::utility, price)
    , m_group(group)
    , m_rents(rents)
{
}

int Utility::group() const
{
    return m_group;
}

int Utility::rent(const Board & board, int distanceTravelled) const
{
    int utilities = 0;
    
    for (size_t i = 0; i < board.size(); ++i)
    {
        auto field = board[i];

        if (auto util = dynamic_cast<const Utility*>(field))
        {
            if (m_owner == util->owner()
             && m_group == util->group())
               ++utilities;
        }
    }

    return distanceTravelled * m_rents[utilities-1];
}

QJsonObject Utility::description()
{
    auto description = OwnableField::description();
    description["group"] = m_group;
    description["rent"] = rents();
    return description;
}

QJsonArray Utility::rents() const
{
    QJsonArray jsonRents;
    for (auto r : m_rents)
    {
        jsonRents.append(r);
    }

    return jsonRents;
}
