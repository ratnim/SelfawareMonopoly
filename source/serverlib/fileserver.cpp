#include "fileserver.h"

#include <QDebug>
#include <QDir>
#include <QFile>

QByteArray FileServer::handle(const Request request)
{
    static const auto routes = createRoutes();

    const auto route = routes.find(request.path);
    if (route != routes.end())
    {
        return staticPage(route->second);
    }
    return Request::generateHttpError(404);
}

std::map<QString, QString> FileServer::createRoutes()
{
    // TODO: It is possible to parse env(STATIC_SERVER_DATA) here to whitelist every file that is in the directory.
    return {
        { "/lobby", "lobby.html" },
        { "/game", "game.html" }
    };
}

QByteArray FileServer::staticPage(const QString& filename)
{
    static const QDir dir(QString(qgetenv("STATIC_SERVER_DATA")));

    QFile file(dir.absoluteFilePath(filename));
    if (file.open(QIODevice::ReadOnly))
    {
        return Request::toHttpAnswer(file.readAll());
    }

    qWarning() << "Could not open " << filename;
    return Request::generateHttpError(404);
}
