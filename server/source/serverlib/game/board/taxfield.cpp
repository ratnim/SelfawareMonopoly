
#include <game/board/taxfield.h>

#include <game/game.h>
#include <game/turn/paystate.h>

TaxField::TaxField(const QString& name, int amount)
: Field(name, FieldType::tax)
, m_amount(amount)
{
}

QJsonObject TaxField::description()
{
    auto descr = Field::description();
    descr["amount"] = m_amount;
    return descr;
}

bool TaxField::moveOn(const QString& player, Game* game, int)
{
    std::vector<Debt> debts;
    debts.emplace_back(player, "", amount());
    game->stateChange<PayState>(debts);
    return true;
}

int TaxField::amount() const
{
    return m_amount;
}
