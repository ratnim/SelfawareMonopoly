#include "server.h"

#include "event.h"
#include "request.h"

#include <QDir>
#include <QFile>
#include <QTcpSocket>

Server::Server()
    : QTcpServer(nullptr)
{
    setMaxPendingConnections(1024);
    listen(QHostAddress::Any, 80);

    m_paths.emplace_back(Request::GET, "/", [](const Request&) { return staticPage("lobby.html"); });
    m_paths.emplace_back(Request::GET, "/lobby", [](const Request&) { return staticPage("lobby.html"); });
    m_paths.emplace_back(Request::GET, "/game", [](const Request&) { return staticPage("game.html"); });

    m_paths.emplace_back(Request::POST, "/lobby", [this](const Request& request) { return handleLobby(request); });
    m_paths.emplace_back(Request::POST, "/game", [this](const Request& request) { return handleGame(request); });
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
    auto request = Request::fromString(QString(data));

    QString answer;
    for (auto& path : m_paths)
    {
        answer += path.match(request);
    }

    /*
    if (request.m_path == "/")
    {
        return Request::toHttpRequest(response);
    }
    else if (path == "/game")
    {
        qDebug().noquote() << Request::extractData(QString(data));

        auto event = Event::fromString(data);
        //event->handle(m_state);
        m_events.push_back(std::move(event));

        return Request::toHttpRequest(data);
    }*/

    return Request::toHttpRequest(answer);
}

void Server::finish(QTcpSocket* socket, const QByteArray& data)
{
    socket->write(data);
    socket->flush();
    socket->close();
}

QString Server::handleLobby(const Request& request)
{
    qDebug().noquote() << request.m_body;
    return request.m_body;
}

QString Server::handleGame(const Request& request)
{
    qDebug().noquote() << request.m_body;
    return request.m_body;
}

QString Server::staticPage(const QString& filename)
{
    QFile file("../../../static/" + filename);
    file.open(QIODevice::ReadOnly);
    return file.readAll();
}
