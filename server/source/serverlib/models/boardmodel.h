#pragma once

#include <game/board/board.h>
#include <utils/staticstorage.h>
#include <QDir>

class BoardModel : public StaticStorage<BoardModel>
{
public:
    BoardModel();
    BoardModel(const QString& boradDir);
    static void setBoardDir(const QString& path);

    Board newBoard(const QString& filename) const;

protected:
    QDir m_boardDir;

    QString getPath(const QString& filename) const;
    QString loadBoardFile(QString& path) const;
    
	static QJsonObject parseBoardFile(const QString& json);
    static std::vector<std::unique_ptr<Field>> createFields(const QJsonObject& jObject);
};