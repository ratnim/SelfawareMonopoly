#pragma once

#include <array>

#include <QString>

#include <game/board/field.h>


enum ConstructionLevel
{
    BASE = 0,
    HOUSE_1 = 1,
    HOUSE_2 = 2,
    HOUSE_3 = 3,
    HOUSE_4 = 4,
    HOTEL = 5,
};

class Street : public Field
{
public:
    Street(const QString& name, int group, int price, int housePrice, std::array<int, ConstructionLevel::HOTEL + 1> rents);

    int group() const;

    int price() const;
    int housePrice() const;
    ConstructionLevel constructionLevel() const;
    int rent() const;

	void changeOwner(const QString& newOwner);

    QString owner() const;

protected:
    QString m_owner;
    const int m_group;
    const int m_price;
    const int m_housePrice;
    ConstructionLevel m_constructionLevel;
    const std::array<int, ConstructionLevel::HOTEL + 1> m_rents;
};
