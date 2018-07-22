#include "field.h"

#include <QMetaEnum>

FieldTypeStringConverter::FieldType FieldTypeStringConverter::typeByName(const QString& string)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<FieldTypeStringConverter::FieldType>();
    QByteArray latin1 = string.toLatin1();
    int result = metaEnum.keyToValue(latin1.constData());
    return static_cast<FieldTypeStringConverter::FieldType>(result);
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
