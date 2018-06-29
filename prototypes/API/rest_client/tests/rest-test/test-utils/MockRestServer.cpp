
#include <gmock/gmock.h>

#include "MockRestServer.h"

MockRestServer::MockRestServer()
: m_tcpServer()
{
    m_tcpServer.listen(QHostAddress::LocalHost, 80);
    QObject::connect(&m_tcpServer, &QTcpServer::newConnection, [this](){connected();});
}

MockRestServer::~MockRestServer()
{
    m_tcpServer.close();
}

void MockRestServer::connected()
{
    auto connection = m_tcpServer.nextPendingConnection();
    QObject::connect(connection, &QTcpSocket::readyRead, [this, connection](){reply(connection);});
}

void MockRestServer::reply(QTcpSocket* connection)
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
        connection->write(
R"(HTTP/1.0 404 Not Found
Connection: close

)");
//        connection->close();
        connection->deleteLater();
        return;
    }

    static auto acceptedTypes = QStringList() << "GET" << "POST" << "PUT" << "DELETE";

    if (acceptedTypes.count(requestType) != 1)
    {
        // 400
        connection->write(
R"(HTTP/1.0 400 Bad Request
Connection: close

)");
//        connection->close();
        connection->deleteLater();
        return;
    }

    // 200
    connection->write(QString(
R"(HTTP/1.0 200 OK
Connection: close
Content-Length: %1

%2)").arg(QString(std::to_string(requestType.length()).c_str()), requestType).toStdString().c_str());
//    connection->close();
    connection->deleteLater();
}
