#include "server.h"

#include "request.h"

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
        auto answer = handle(socket->readAll());
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

QByteArray Server::handle(const QByteArray& data)
{
    qDebug().noquote() << Request::extractPath(QString(data));
    return Request::toHttpRequest(data);
}

void Server::finish(QTcpSocket* socket, const QByteArray& data)
{
    socket->write(data);
    socket->flush();
    socket->close();
}
