#pragma once

#include <game/board/field.h>

class TaxField : public Field
{
public:
    TaxField(const QString& name, int amount);

    int amount() const;

    QJsonObject description() override;
    bool moveOn(const QString& player, Game* game, int distanceTraveled) override;

protected:
    int m_amount;
};