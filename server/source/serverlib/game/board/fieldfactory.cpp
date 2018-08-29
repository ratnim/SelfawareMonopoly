#include "fieldfactory.h"

#include <game/board/street.h>

std::unique_ptr<Field> FieldFactory::create(const QJsonObject& specification)
{
    auto name = specification["name"].toString();
    auto type = FieldTypeStringConverter::typeByName(specification["type"].toString());

    if (type == FieldType::street)
    {
        return std::make_unique<Street>(name);
    }
    return std::make_unique<Field>(name, type);
}