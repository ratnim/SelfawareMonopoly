#pragma once

#include <vector>

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

class TaxField : public Field
{
public:
    TaxField(int amount);

    int amount() const;

protected:
    int m_amount;
};

class Player;

class PropertyField : public Field
{
public:
    PropertyField();

    int group();

    int price();
    int rent();

    Player* owner();

protected:
    Player* m_owner;
};

class Board
{
public:
    Board(Board& prototype);

    static Board& prototype();

    Field* operator[](size_t index);

    std::vector<Field> m_fields;

protected:
    Board();
};
