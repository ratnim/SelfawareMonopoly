#pragma once

#include <QObject>
#include <QString>

#include <game/board/field.h>

class Game;
class Board;

class OwnableField : public Field
{
public:
    OwnableField(const QString& name, const FieldType type, const int price);

    int price() const;
    virtual int rent(const Board & board, const int distanceTraveled) const = 0;
    QString owner() const;

    void changeOwner(const QString& newOwner);

    QJsonObject description() override;

    bool moveOn(const QString& playerName, Game* game, int distanceTraveled) override;

protected:
    QString m_owner;
    const int m_price;
};