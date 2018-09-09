#include "ownablefield.h"

#include <QMetaEnum>
#include <QJsonObject>

#include <game/game.h>

#include <game/turn/buystate.h>
#include <game/turn/paystate.h>

OwnableField::OwnableField(const QString& name, const FieldType type, const int price)
: Field(name, type)
, m_price(price)
{
}

int OwnableField::price() const
{
    return m_price;
}

QString OwnableField::owner() const
{
    return m_owner;
}

void OwnableField::changeOwner(const QString & newOwner)
{
    m_owner = newOwner;
}

QJsonObject OwnableField::description()
{
    auto descr = Field::description();
    descr["price"] = m_price;
    return descr;
}

bool OwnableField::moveOn(const QString& playerName, Game* game)
{
    bool stateChanged = false;

    if (m_owner == "")
    {
        game->stateChange<BuyState>();
        stateChanged = true;
    }
    else if (m_owner != playerName)
    {
        std::vector<Debt> debts;
        debts.emplace_back(playerName, m_owner, rent(game->board()));
        game->stateChange<PayState>(debts);
        stateChanged = true;
    }
    return stateChanged;
}
