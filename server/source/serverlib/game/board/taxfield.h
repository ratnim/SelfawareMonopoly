#pragma once

#include <game/board/field.h>

class TaxField : public Field
{
public:
    TaxField(int amount);

    int amount() const;

protected:
    int m_amount;
};