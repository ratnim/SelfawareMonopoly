#pragma once

#include <QString>

struct ConnectionRequest
{
    ConnectionRequest(const QString& route, const QString& session, int gameId);
    static ConnectionRequest fromUrl(const QString& url);

    const QString route;
    const QString session;
    const int gameId;
};
