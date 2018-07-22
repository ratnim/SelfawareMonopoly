#pragma once

#include <QJsonObject>

#include <game/board/field.h>

class FieldFactory
{
    FieldFactory() = delete;

	public:
    static Field create(const QJsonObject& specification);
};
