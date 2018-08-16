#pragma once

#include <QString>

struct Request
{
    Request(const QString& route, const QString& session, int gameId);
    static Request fromUrl(const QString& url);

    const QString route;
    const QString session;
    const int gameId;
};
