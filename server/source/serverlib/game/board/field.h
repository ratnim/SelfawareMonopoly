#pragma once 

#include <QObject>
#include <QString>

class FieldTypeStringConverter : QObject
{
    Q_OBJECT
public:
    enum FieldType
    {
        start,
        street,
        station,
        event_card,
        society_card,
        prison,
        free,
        go_to_prison,
        tax,
        utility
    };
    Q_ENUM(FieldType)

    static FieldTypeStringConverter::FieldType typeByName(const QString& string);
    static QString nameByType(FieldType type);
};

using FieldType = FieldTypeStringConverter::FieldType;


class Field
{
public:
    Field(const QString& name, const FieldType type);

    QString name() const;
    FieldType type() const;
	
	virtual QJsonObject description() const;

protected:
    const QString m_name;
    const FieldType m_type;
};