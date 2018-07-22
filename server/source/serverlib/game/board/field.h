#pragma once 

#include <QObject>
#include <QString>

class FieldTypeStringConverter : QObject
{
    Q_OBJECT
public:
    enum FieldType
    {
        Start,
        Prison,
        Free,
        GotoPrison,
        IncomeTax,
        SalesTax,
        Street,
        Station,
        Plant,
        EventCard,
        SocietyCard
    };
    Q_ENUM(FieldType)

    static FieldTypeStringConverter::FieldType typeByName(const QString& string);
};

using FieldType = FieldTypeStringConverter::FieldType;


class Field
{
public:
    Field(const QString& name, const FieldType type);

    QString name() const;
    FieldType type() const;

protected:
    const QString m_name;
    const FieldType m_type;
};