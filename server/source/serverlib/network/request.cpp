#include "request.h"

#include <QUrlQuery>

Request Request::fromUrl(const QString& url)
{
    QString route, session;
    int game_id;

    const QString path = url.split('/').back();

    const auto arguments = path.split('?');
    route = arguments.front();

    if (arguments.size() > 1)
    {
        QUrlQuery args(arguments.back());
        session = args.queryItemValue("session");
        game_id = args.queryItemValue("game_id").toInt();
    }

    return { route, session, game_id };
}
