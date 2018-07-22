#pragma once

#include <array>

#include <QString>

#include <game/board/field.h>

class Player;

class PropertyField : public Field
{
public:
    PropertyField();

    int group();

    int price();
    int rent();

    Player* owner();

protected:
    Player* m_owner;
};

class StreetInfo
{
public:
protected:
    QString m_name;
    int m_group;
    std::array<int, 6> m_prices;
};