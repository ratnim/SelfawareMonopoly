#pragma once

#include <array>

#include <QString>
#include <QJsonObject>
#include <QJsonArray>

#include <game/board/ownablefield.h>


class Utility : public OwnableField
{
public:
    Utility(const QString& name, int group, int price, std::vector<int> rents);

    int group() const;
    int rent(const Board & boar, int distanceTraveled) const override;

	QJsonObject description() override;

protected:
    QJsonArray rents() const;

    const int m_group;
    const std::vector<int> m_rents;
};
