#include "field.h"

#include <QMetaEnum>
#include <QJsonObject>

#include <game/game.h>

FieldTypeStringConverter::FieldType FieldTypeStringConverter::typeByName(const QString& string)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<FieldTypeStringConverter::FieldType>();
    QByteArray latin1 = string.toLatin1();
    int result = metaEnum.keyToValue(latin1.constData());
    if (result < 0)
        throw new std::runtime_error("Type: " + string.toStdString() + " is not supported.");
    return static_cast<FieldTypeStringConverter::FieldType>(result);
}

QString FieldTypeStringConverter::nameByType(FieldType type)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<FieldTypeStringConverter::FieldType>();
    QString name{metaEnum.valueToKey(type)};
    if (name.isEmpty())
        throw new std::runtime_error("Type with value: " + QString(type).toStdString() + " is not supported.");
    return name;
}

Field::Field(const QString& name, const FieldType type) : 
	m_name(name)
	, m_type(type)
{
}

QString Field::name() const
{
    return m_name;
}

FieldType Field::type() const
{
    return m_type;
}

QJsonObject Field::description()
{
    return {
        { "name", m_name },
        { "type", FieldTypeStringConverter::nameByType(m_type) }
	};
}

bool Field::moveOn(const QString& playerName, Game* game, int distanceTraveled)
{
    return false;
}

void Field::passBy(const QString& playerName, Game* game)
{
}
