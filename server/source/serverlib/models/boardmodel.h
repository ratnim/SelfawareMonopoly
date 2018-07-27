#pragma once

#include <game/board/board.h>
#include <utils/staticstorage.h>
#include <QDir>

class BoardModel : public StaticStorage<BoardModel>
{
public:
    BoardModel(const QString& boradDir);
    static void setBoardDir(const QString& path);

    Board new_board(const QString& filename) const;

protected:
    QDir m_boardDir;

    QString getPath(const QString& filename) const;
    QString loadBoardFile(QString& path) const;
    
	static QJsonObject parseBoardFile(const QString& json);
    static std::vector<Field> createFields(const QJsonObject& jObject);

	void setDir(const QString& path);
    void checkDir();
};