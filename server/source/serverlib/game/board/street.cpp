#include "street.h"

Street::Street(const QString& name, int group, int price, int housePrice, std::array<int, ConstructionLevel::HOTEL + 1> rents)
    : OwnableField(name, FieldType::street, price)
    , m_group(group)
    , m_housePrice(housePrice)
    , m_constructionLevel(ConstructionLevel::BASE)
    , m_rents(rents)
{
}

void Street::changeConstructionLevel(const ConstructionLevel newLevel)
{
    m_constructionLevel = newLevel;
}

int Street::group() const
{
    return m_group;
}

int Street::housePrice() const
{
    return m_housePrice;
}

ConstructionLevel Street::constructionLevel() const
{
    return m_constructionLevel;
}

int Street::rent() const
{
    return m_rents[m_constructionLevel];
}

QJsonObject Street::description()
{
    auto description = OwnableField::description();
    description["group"] = m_group;
    description["house_price"] = m_housePrice;
    description["rent"] = rents();
    return description;
}

QJsonArray Street::rents() const
{
    QJsonArray jsonRents;
    for (int i = 0; i < ConstructionLevel::HOTEL + 1; ++i)
    {
        jsonRents.append(m_rents[i]);
    }

    return jsonRents;
}
