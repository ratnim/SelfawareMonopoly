#pragma once

#include <array>

#include <QString>
#include <QJsonObject>
#include <QJsonArray>

#include <game/board/ownablefield.h>


enum ConstructionLevel
{
    BASE = 0,
    HOUSE_1 = 1,
    HOUSE_2 = 2,
    HOUSE_3 = 3,
    HOUSE_4 = 4,
    HOTEL = 5,
};

class Street : public OwnableField
{
public:
    Street(const QString& name, int group, int price, int housePrice, std::array<int, ConstructionLevel::HOTEL + 1> rents);

    int group() const;
    int housePrice() const;
    ConstructionLevel constructionLevel() const;
    int rent() const override;
    void changeConstructionLevel(const ConstructionLevel newLevel);

	QJsonObject description() override;

protected:
    QJsonArray rents() const;

    const int m_group;
    const int m_housePrice;
    ConstructionLevel m_constructionLevel;
    const std::array<int, ConstructionLevel::HOTEL + 1> m_rents;
};
