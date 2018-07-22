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
};

using FieldType = FieldTypeStringConverter::FieldType;

class Field
{
public:
    Field(const QString& name, FieldType type);

    QString name() const;
    FieldType type() const;

protected:
    const QString m_name;
    const FieldType m_type;
};