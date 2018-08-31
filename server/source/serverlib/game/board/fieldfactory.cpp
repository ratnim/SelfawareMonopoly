#include "fieldfactory.h"

#include <array>

#include <QJsonArray>

#include <game/board/start.h>
#include <game/board/street.h>
#include <game/board/gotojail.h>

std::unique_ptr<Field> FieldFactory::create(const QJsonObject& specification)
{
    auto name = specification["name"].toString();
    auto type = FieldTypeStringConverter::typeByName(specification["type"].toString());

	switch (type)
	{
    case FieldType::start:
        return std::make_unique<Start>(name);
    case FieldType::street:
        return createStreet(specification);
    case FieldType::go_to_jail:
        return std::make_unique<GoToJail>(name);
    default:
        return std::make_unique<Field>(name, type);
	}
}


std::unique_ptr<Field> FieldFactory::createStreet(const QJsonObject& specification)
{
    auto name = specification["name"].toString();
    int group = specification["group"].toInt();
    int price = specification["price"].toInt();
    int housePrice = specification["house_price"].toInt();
    auto jsonRents = specification["rent"].toArray();

    const int differentRents = ConstructionLevel::HOTEL + 1;
    std::array<int, differentRents> rents;
    for (int i = 0; i < differentRents; ++i)
    {
        rents[i] = jsonRents[i].toInt();
    }

    return std::make_unique<Street>(name, group, price, housePrice, rents);
}
