#pragma once

#include <routes/route.h>

class OverviewRoute : public Route
{
public:
    OverviewRoute(QObject* parent, const Request& request);

protected:
    void enterLobby(const QJsonValue& data);
    static QString enterLobbyAnswer(const QString& userSession);
};
