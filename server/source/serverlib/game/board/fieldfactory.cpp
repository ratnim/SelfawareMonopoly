#include "fieldfactory.h"

Field FieldFactory::create(const QJsonObject& specification)
{
    auto name = specification["name"].toString();
    auto type = FieldTypeStringConverter::typeByName( specification["type"].toString());

    return Field(name, type);
}