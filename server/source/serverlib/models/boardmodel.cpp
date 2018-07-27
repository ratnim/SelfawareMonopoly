#include "boardmodel.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include <game/board/fieldfactory.h>

Board BoardModel::new_board() const
{
    QString filename = "./assets/boards/berlin.json";
    
	auto json = loadBoardFile(filename);
    auto jObject = parseBoardFile(json);
    auto fields = createFields(jObject);

    return Board(fields);
}

QString BoardModel::loadBoardFile(const QString& filename)
{
    QString json;
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    json = file.readAll();
    file.close();

	return json;
}

QJsonObject BoardModel::parseBoardFile(const QString& json)
{
    auto jsonDoc = QJsonDocument::fromJson(json.toUtf8());
    return jsonDoc.object();
}

std::vector<Field> BoardModel::createFields(const QJsonObject& jObject)
{
    auto field_specification = jObject["fields"].toArray();
    std::vector<Field> fields;

    foreach (const QJsonValue& specification, field_specification)
    {
        QJsonObject obj = specification.toObject();
        auto field = FieldFactory::create(obj);
        fields.push_back(field);
    }
    return fields;
}