#include "server.h"

#include "event.h"
#include "request.h"
#include "fileserver.h"

#include <QTcpSocket>

Server::Server()
    : QTcpServer(nullptr)
{
    setMaxPendingConnections(1024);
    listen(QHostAddress::Any, 80);
}

void Server::run()
{
    forever
    {
        auto socket = acccept();
        auto answer = handle(QString(socket->readAll()));
        finish(socket, answer);
    }
}

QTcpSocket* Server::acccept()
{
    if (!waitForNewConnection(-1))
    {
        throw std::runtime_error("Internal server error.");
    }
    auto socket = nextPendingConnection();

    // Waiting forever is a potential dos.
    socket->waitForReadyRead(-1);
    return socket;
}

QByteArray Server::handle(const QString& data)
{
    auto request = Request::fromString(data);

    qDebug().noquote() << data;

    switch (request.type)
    {
    case Request::GET:
        return FileServer::handle(request);

    case Request::POST:
        return m_state.handle(request);
    }

    qWarning() << data;
    return Request::generateHttpError(404);
}

void Server::finish(QTcpSocket* socket, const QByteArray& data)
{
    socket->write(data);
    socket->flush();
    socket->close();
}
