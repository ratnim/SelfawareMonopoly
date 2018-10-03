#pragma once

#include <array>

#include <QString>
#include <QJsonObject>
#include <QJsonArray>

#include <game/board/ownablefield.h>


class Station : public OwnableField
{
public:
    Station(const QString& name, int group, int price, int baseRent);

    int group() const;
    int rent(const Board & board, int distanceTravelled) const override;

	QJsonObject description() override;

protected:
    const int m_group;
    const int m_baseRent;
};
