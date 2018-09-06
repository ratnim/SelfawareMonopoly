#pragma once

#include <memory>
#include <vector>

#include <QJsonArray>
#include <QString>

#include <game/board/field.h>

bool containsRequest(const QJsonArray& possibleRequests, const QString& request);

std::vector<std::unique_ptr<Field>> fieldsFree();
std::vector<std::unique_ptr<Field>> fieldsSingleJail();
std::vector<std::unique_ptr<Field>> fieldsJailGoToJail();
std::vector<std::unique_ptr<Field>> fieldsStreets();
std::vector<std::unique_ptr<Field>> fieldsStart();
std::vector<std::unique_ptr<Field>> fieldsTwoGroups();
