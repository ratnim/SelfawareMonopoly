#pragma once

#include <QJsonObject>
#include <memory>

#include <game/board/field.h>

class FieldFactory
{

    FieldFactory() = delete;

public:
   
	static std::unique_ptr<Field> create(const QJsonObject& specification);

};
