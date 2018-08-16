#include "fieldfactory.h"

std::unique_ptr<Field> FieldFactory::create(const QJsonObject& specification)
{
    auto name = specification["name"].toString();
    auto type = FieldTypeStringConverter::typeByName(specification["type"].toString());

    return std::make_unique<Field>(name, type);
}