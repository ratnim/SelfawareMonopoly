#include "fileserver.h"

#include <QFile>
#include <QTcpSocket>

#include "request.h"

FileServer::FileServer(const QString& rootDirectory)
    : QTcpServer(nullptr)
    , m_rootDirectory(rootDirectory)
{
    setMaxPendingConnections(1024);
    listen(QHostAddress::Any, 80);

    connect(this, &QTcpServer::newConnection, [this]() 
    { 
        auto socket = acccept();
        finish(socket, handle(socket->readAll()));
    });
}

QTcpSocket* FileServer::acccept()
{
    auto socket = nextPendingConnection();

    // Waiting forever is a potential dos.
    socket->waitForReadyRead(-1);
    return socket;
}

void FileServer::finish(QTcpSocket* socket, const QByteArray& data)
{
    socket->write(data);
    socket->flush();
    socket->close();
}

QByteArray FileServer::handle(const QString& data)
{
    static const auto routes = createRoutes();

    const auto path = Request::extractPath(data);
    const auto route = routes.find(path);
    if (route != routes.end())
    {
        return staticPage(route->second);
    }

    return Request::generateHttpError(404);
}

std::map<QString, QString> FileServer::createRoutes()
{
    // TODO: It is possible to parse m_rootDirectory here to whitelist every file that is in the directory.
    return {
        { "/lobby", "lobby.html" },
        { "/game", "game.html" }
    };
}

QByteArray FileServer::staticPage(const QString& filename)
{
    QFile file(m_rootDirectory.absoluteFilePath(filename));
    if (file.open(QIODevice::ReadOnly))
    {
        return Request::toHttpAnswer(file.readAll());
    }

    qWarning() << "Could not open " << filename;
    return Request::generateHttpError(404);
}
