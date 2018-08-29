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
    Street(const QString& name);

    int group();

    int price();
    int rent();

    QString owner();

protected:
    QString m_owner;
};

class StreetInfo
{
public:
protected:
    QString m_name;
    int m_group;
    std::array<int, ConstructionLevel::HOTEL + 1> m_prices;
};