#pragma once

#include <game/board/board.h>
#include <utils/staticstorage.h>

class BoardModel : public StaticStorage<BoardModel>
{
public:
    Board new_board() const;

protected:
    static QString loadBoardFile(const QString& filename);
    static QJsonObject parseBoardFile(const QString& json);
    static std::vector<Field> createFields(const QJsonObject& jObject);
};