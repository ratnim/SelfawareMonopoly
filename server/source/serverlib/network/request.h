#pragma once

#include <QString>

struct Request
{
    static Request fromUrl(const QString& url);

    const QString route;
    const QString session;
    const int gameId;
};
