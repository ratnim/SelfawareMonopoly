#include "helpers.h"

#include <QJsonObject>

#include <game/board/gotojail.h>
#include <game/board/start.h>
#include <game/board/street.h>
#include <game/board/station.h>
#include <game/board/utility.h>
#include <game/board/taxfield.h>

bool containsRequest(const QJsonArray& possibleRequests, const QString& request)
{
    for (const auto requestObj : possibleRequests)
    {
        auto name = requestObj.toObject()["request"].toString();
        auto namestd = name.toStdString();
        if (name == request)
        {
            return true;
        }
    }
    return false;
}

std::vector<std::unique_ptr<Field>> fieldsSingleJail()
{
    std::vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("jail", FieldType::jail)));
    return fields;
}

std::vector<std::unique_ptr<Field>> fieldsFree()
{
    std::vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    return fields;
}

std::vector<std::unique_ptr<Field>> fieldsJailGoToJail()
{
    std::vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<GoToJail>("go to jail")));
    fields.push_back(std::move(std::make_unique<Field>("jail", FieldType::jail)));
    return fields;
}

std::vector<std::unique_ptr<Field>> fieldsStreets()
{
    std::vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::move(std::make_unique<Street>("street", 0, 100, 50, std::array<int, ConstructionLevel::HOTEL + 1>{ { 10, 20, 30, 40, 50, 60 } })));
    return fields;
}

std::vector<std::unique_ptr<Field>> fieldsStart()
{
    std::vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::move(std::make_unique<Start>("start")));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    return fields;
}

std::vector<std::unique_ptr<Field>> fieldsTwoGroups()
{
    std::vector<std::unique_ptr<Field>> fields;
    fields.emplace_back(new Street("street A1", 0, 100,  50, std::array<int, ConstructionLevel::HOTEL + 1> {1, 2, 3, 4,  5,  6}));
    fields.emplace_back(new Street("street A2", 0, 100,  50, std::array<int, ConstructionLevel::HOTEL + 1> {1, 2, 3, 4,  5,  6}));
    fields.emplace_back(new Street("street B1", 1, 150, 100, std::array<int, ConstructionLevel::HOTEL + 1> {2, 4, 6, 8, 10, 12}));
    fields.emplace_back(new Street("street B2", 1, 150, 100, std::array<int, ConstructionLevel::HOTEL + 1> {2, 4, 6, 8, 10, 12}));
    return fields;
}

std::vector<std::unique_ptr<Field>> fieldsTax()
{
    std::vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::move(std::make_unique<Start>("start")));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<Field>("free", FieldType::free)));
    fields.push_back(std::move(std::make_unique<TaxField>("tax", 100)));
    return fields;
}

std::vector<std::unique_ptr<Field>> fieldsStations()
{
    std::vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::move(std::make_unique<Start>("start")));
    fields.push_back(std::move(std::make_unique<Station>("stationA", 0, 200, 100)));
    fields.push_back(std::move(std::make_unique<Station>("stationB", 0, 200, 100)));
    fields.push_back(std::move(std::make_unique<Station>("stationC", 0, 200, 100)));
    fields.push_back(std::move(std::make_unique<Station>("stationD", 1, 500, 200)));
    return fields;
}

std::vector<std::unique_ptr<Field>> fieldsUtilities()
{
    std::vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::move(std::make_unique<Start>("start")));
    fields.push_back(std::move(std::make_unique<Utility>("utilA", 0, 200, std::vector<int>{2, 3, 5})));
    fields.push_back(std::move(std::make_unique<Utility>("utilB", 0, 200, std::vector<int>{2, 3, 5})));
    fields.push_back(std::move(std::make_unique<Utility>("utilC", 0, 200, std::vector<int>{2, 3, 5})));
    fields.push_back(std::move(std::make_unique<Utility>("utilD", 1, 500, std::vector<int>{5})));
    return fields;
}
