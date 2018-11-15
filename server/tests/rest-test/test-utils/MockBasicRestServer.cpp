
#include <gmock/gmock.h>

#include "MockBasicRestServer.h"

MockBasicRestServer::MockBasicRestServer()
: m_tcpServer()
{
    m_tcpServer.listen(QHostAddress::LocalHost, 80);
    QObject::connect(&m_tcpServer, &QTcpServer::newConnection, [this](){connected();});
}

MockBasicRestServer::~MockBasicRestServer()
{
    m_tcpServer.close();
}

void MockBasicRestServer::connected()
{
    auto connection = m_tcpServer.nextPendingConnection();
    QObject::connect(connection, &QTcpSocket::readyRead, [this, connection](){reply(connection);});
}

void MockBasicRestServer::reply(QTcpSocket* connection)
{
    auto request = QString(connection->readAll());

    auto firstSplit = request.split(' ');
    auto requestType = firstSplit[0];
    auto firstRemainder = firstSplit[1];

    auto secondSplit = firstRemainder.split(' ');
    auto requestPath = secondSplit[0];
    // we don't care about the rest

    if (requestPath != "/")
    {
        // 404
        connection->write("HTTP/1.0 404 Not Found\n\n");
        return;
    }

    static auto acceptedTypes = QStringList() << "GET" << "POST" << "PUT" << "DELETE";

    if (acceptedTypes.count(requestType) != 1)
    {
        // 400
        connection->write("HTTP/1.0 400 Bad Request\n\n");
        return;
    }

    // 200
    connection->write((QString("HTTP/1.0 200 OK\nContent-Length: %1\nContent-Type: text/plain; charset=us-ascii\n\n").arg(requestType.size()) + requestType).toStdString().c_str());
}
