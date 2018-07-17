
#include <gmock/gmock.h>

#include "MockCoinhiveServer.h"

#include <QUrlQuery>
#include <QJsonDocument>

const QString topAnswer = R"({
    "success": true,
    "users": [
        {
            "name": "Rich Guy",
            "total": 14096,
            "withdrawn": 10000,
            "balance": 4096
        },
        {
            "name": "Poor Guy",
            "total": 1050,
            "withdrawn": 0,
            "balance": 1050
        },
        {
            "name": "Broke Bloke",
            "total": 1024,
            "withdrawn": 1024,
            "balance": 0
        }
    ]
})";

const QString withdrawAnswer = R"({
    "success": true,
    "name": "%1",
    "amount": %2
})";

MockCoinhiveServer::MockCoinhiveServer()
: m_tcpServer()
{
    m_tcpServer.listen(QHostAddress::LocalHost, 80);
    QObject::connect(&m_tcpServer, &QTcpServer::newConnection, [this](){connected();});
}

MockCoinhiveServer::~MockCoinhiveServer()
{
    m_tcpServer.close();
}

void MockCoinhiveServer::connected()
{
    auto connection = m_tcpServer.nextPendingConnection();
    QObject::connect(connection, &QTcpSocket::readyRead, [this, connection](){reply(connection);});
}

void MockCoinhiveServer::reply(QTcpSocket* connection)
{
    auto request = QString(connection->readAll());

    auto firstSplit = request.split(' ');
    auto requestType = firstSplit[0];
    auto firstRemainder = firstSplit[1];

    auto secondSplit = firstRemainder.split(' ');
    auto requestResource = secondSplit[0];
    // we don't care about the rest

    auto resourceSplit = requestResource.split('?');
    auto resourcePath = resourceSplit[0];
    auto parameters = QUrlQuery(resourceSplit[1]);

    if (resourcePath == "/user/top")
    {
        const auto header = QString("HTTP/1.0 200 OK\nContent-Length: %1\nContent-Type: text/plain; charset=us-ascii\n\n").arg(topAnswer.size());
        const auto body = topAnswer;

        connection->write((header+body).toStdString().c_str());
        return;
    }

    if (resourcePath == "/user/withdraw")
    {
        const auto user = parameters.queryItemValue("name");
        const auto amount = parameters.queryItemValue("amount");

        const auto body = withdrawAnswer.arg(user, amount);
        const auto header = QString("HTTP/1.0 200 OK\nContent-Length: %1\nContent-Type: text/plain; charset=us-ascii\n\n").arg(body.size());

        connection->write((header+body).toStdString().c_str());
        return;
    }

    connection->write("HTTP/1.0 400 Bad Request\n\n");
    return;
}
