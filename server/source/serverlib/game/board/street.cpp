#include "street.h"

Street::Street(const QString& name, int group, int price, int housePrice, std::array<int, ConstructionLevel::HOTEL + 1> rents)
    : Field(name, FieldType::street)
    , m_group(group)
    , m_price(price)
    , m_housePrice(housePrice)
    , m_constructionLevel(ConstructionLevel::BASE)
    , m_rents(rents)
{
}

void Street::changeOwner(const QString& newOwner)
{
    m_owner = newOwner;
}

int Street::group() const
{
    return m_group;
}

QString Street::owner() const
{
    return m_owner;
}

int Street::price() const
{
    return m_price;
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
    auto description = Field::description();
    description["group"] = m_group;
    description["price"] = m_price;
    description["house_price"] = m_housePrice;
    description["construction_level"] = m_constructionLevel;
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
