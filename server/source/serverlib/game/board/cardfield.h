#pragma once 

#include <game/board/field.h>
#include <game/cardstack.h>


class CardField : public Field
{
public:

public:
    CardField(const QString& name, FieldType type);

    bool moveOn(const QString& playerName, Game* game, int distanceTraveled) override;

protected:
    FieldType m_type;
};