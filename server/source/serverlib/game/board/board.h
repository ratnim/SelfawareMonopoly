#pragma once

#include <QObject>
#include <QString>

#include <memory>
#include <vector>

#include <game/board/field.h>
#include <game/board/street.h>

class Board : public QObject
{
    Q_OBJECT
public:
    Board(std::vector<std::unique_ptr<Field>> fields);
    size_t size() const;

    QJsonObject description() const;

    int jailIndex() const;
    Field* operator[](size_t index);
    const Field* operator[](size_t index) const;

    int targetForMove(int position, int distance);
    int distanceToNextField(int position, FieldType type) const;

	std::vector<int> ownedGroups(const QString& playerName);
	bool isGroupOwner(const QString& playerName, int groupId) const;
    void changeOwner(int id, const QString& owner);
    void changeConstructionLevels(const QString& owner, const std::vector<std::pair<int,int>>& newLevels);
    void changeConstructionLevel(int id, ConstructionLevel level);
	int fieldPrice(int id);
    int housePrice(int id);

    int calculateConstructionPrice(const QString& owner, const std::vector<std::pair<int,int>>& newLevels);

signals:
    void onPropertyChange(int id, const QString& owner, int consrtuctionLevel);

protected:
    void initializeGroups();
    void findAndSetJailIndex();
    void validateConstructionLevels(const QString& owner, const std::vector<std::pair<int,int>> & levels);

    std::vector<std::unique_ptr<Field>> m_fields;
    std::vector<std::vector<int>> m_groups;
    int m_jailIndex;
};
