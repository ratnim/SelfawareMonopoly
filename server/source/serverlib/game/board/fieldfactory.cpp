#include "fieldfactory.h"

#include <array>

#include <QJsonArray>

#include <game/board/start.h>
#include <game/board/street.h>
#include <game/board/station.h>
#include <game/board/utility.h>
#include <game/board/gotojail.h>
#include <game/board/taxfield.h>

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
    case FieldType::station:
        return std::make_unique<Station>(name, specification["group"].toInt(), specification["price"].toInt(), specification["rent"].toArray()[0].toInt());
    case FieldType::utility:
        return createUtility(specification);
    case FieldType::go_to_jail:
        return std::make_unique<GoToJail>(name);
    case FieldType::tax:
        return std::make_unique<TaxField>(name, specification["rent"].toArray()[0].toInt());
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

std::unique_ptr<Field> FieldFactory::createUtility(const QJsonObject& specification)
{
    auto name = specification["name"].toString();
    int group = specification["group"].toInt();
    int price = specification["price"].toInt();
    auto jsonRents = specification["rent"].toArray();

    const int differentRents = jsonRents.size();
    std::vector<int> rents(differentRents);
    for (int i = 0; i < differentRents; ++i)
    {
        rents[i] = jsonRents[i].toInt();
    }

    return std::make_unique<Utility>(name, group, price, rents);
}
