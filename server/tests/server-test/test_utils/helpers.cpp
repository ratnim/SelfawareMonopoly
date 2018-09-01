#include "helpers.h"

#include <QJsonObject>

#include <game/board/gotojail.h>
#include <game/board/start.h>
#include <game/board/street.h>

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