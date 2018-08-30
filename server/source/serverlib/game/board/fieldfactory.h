#pragma once

#include <QJsonObject>
#include <memory>

#include <game/board/field.h>

class FieldFactory
{

    FieldFactory() = delete;

public:
    
	static std::unique_ptr<Field> create(const QJsonObject& specification);

protected:

	static std::unique_ptr<Field> createStreet(const QJsonObject& specification);
	static std::unique_ptr<Field> createGoToJail(const QJsonObject& specification);
};
