#include "helpers.h"

#include <QJsonObject>

bool containsRequest(const QJsonArray& possibleRequests, const QString& request)
{
    for (const auto requestObj : possibleRequests)
    {
        auto name = requestObj.toObject()["request"].toString();
        auto namestd = name.toStdString();
        if (name == request)
        {
            return true;
        }
    }
    return false;
}