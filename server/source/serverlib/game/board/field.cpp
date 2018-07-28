#include "field.h"

#include <QMetaEnum>
#include <QJsonObject>

FieldTypeStringConverter::FieldType FieldTypeStringConverter::typeByName(const QString& string)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<FieldTypeStringConverter::FieldType>();
    QByteArray latin1 = string.toLatin1();
    int result = metaEnum.keyToValue(latin1.constData());
    return static_cast<FieldTypeStringConverter::FieldType>(result);
}

QString FieldTypeStringConverter::nameByType(FieldType type)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<FieldTypeStringConverter::FieldType>();
    return metaEnum.valueToKey(type);
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

QJsonObject Field::description() const
{
    return {
        { "name", m_name },
        { "type", FieldTypeStringConverter::nameByType(m_type) }
	};
}
