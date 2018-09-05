#pragma once

#include <QObject>
#include <QString>

#include <memory>
#include <vector>

#include <game/board/field.h>

class Board : public QObject
{
    Q_OBJECT
public:
    Board(std::vector<std::unique_ptr<Field>> fields);
    size_t size() const;

    QJsonObject description() const;

    int jailIndex() const;
    Field* operator[](size_t index);

    int targetForMove(int position, int distance);
    void changeOwner(int id, const QString& owner);
    void changeConstructionLevels(const std::vector<std::pair<int,int>>& newLevels);
    int fieldPrice(int id);
    int housePrice(int id);

    int checkHouseChangePrice(const QString& owner, const std::vector<std::pair<int,int>>& newLevels);
    void ensureFullGroupOwnership(const QString& owner, int id);

signals:
    void onPropertyChange(int id, const QString& owner, int consrtuctionLevel);

protected:
    void findAndSetJailIndex();

    std::vector<std::unique_ptr<Field>> m_fields;
    int m_jailIndex;
};
