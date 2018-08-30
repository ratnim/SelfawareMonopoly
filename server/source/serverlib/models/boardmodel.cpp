#include "boardmodel.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <string>

#include <game/board/fieldfactory.h>

BoardModel::BoardModel()
{
    m_boardDir = QDir::current();
}

BoardModel::BoardModel(const QString& boardDir)
	: m_boardDir(QDir(boardDir))
{
}


void BoardModel::setBoardDir(const QString& path)
{
	auto& instance = BoardModel::instance();
	instance.reset(path);
}

 std::vector<std::unique_ptr<Field>> BoardModel::getFieldsForNewBoard(const QString& filename) const
{
	auto path = getPath(filename);
    auto json = loadBoardFile(path);
    auto jObject = parseBoardFile(json);
    auto fields = createFields(jObject);

    return std::move(fields);
}

QString BoardModel::getPath(const QString& filename) const
{
    auto absolutePath = m_boardDir.absoluteFilePath(filename);
    QFile file;
    file.setFileName(absolutePath);
    if (!file.exists())
        throw std::runtime_error("Board file does not exists.");
    return absolutePath;
}

QString BoardModel::loadBoardFile(QString& path) const
{
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    auto json = file.readAll();
    file.close();

    return json;
}

QJsonObject BoardModel::parseBoardFile(const QString& json)
{
    auto jsonDoc = QJsonDocument::fromJson(json.toUtf8());
    return jsonDoc.object();
}

std::vector<std::unique_ptr<Field>> BoardModel::createFields(const QJsonObject& jObject)
{
    auto field_specification = jObject["fields"].toArray();
    std::vector<std::unique_ptr<Field>> fields;

    foreach (const QJsonValue& specification, field_specification)
    {
        QJsonObject obj = specification.toObject();
        auto field = FieldFactory::create(obj);
        fields.push_back(std::move(field));
    }
    return fields;
}
