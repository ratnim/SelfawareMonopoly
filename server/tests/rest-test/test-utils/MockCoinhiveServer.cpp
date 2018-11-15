
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

const QString withdrawAnswerSuccess = R"({
    "success": true,
    "name": "%1",
    "amount": %2
})";

const QString answerFailure = R"({
    "success": false,
    "error": "%2"
})";

const QString headerOK = R"(HTTP/1.0 200 OK
Content-Length: %1
Content-Type: text/plain; charset=us-ascii

)";

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
        if (requestType != "GET")
        {
            const auto body = answerFailure.arg("wrong_method");
            const auto header = headerOK.arg(body.size());
            connection->write((header+body).toLocal8Bit());
            return;
        }

        const auto header = headerOK.arg(topAnswer.size());
        const auto body = topAnswer;

        connection->write((header+body).toStdString().c_str());
        return;
    }

    if (resourcePath == "/user/withdraw")
    {
        if (requestType != "POST")
        {
            const auto body = answerFailure.arg("wrong_method");
            const auto header = headerOK.arg(body.size());
            connection->write((header+body).toLocal8Bit());
            return;
        }

        if (!parameters.hasQueryItem("name") || !parameters.hasQueryItem("amount"))
        {
            const auto body = answerFailure.arg("missing_input");
            const auto header = headerOK.arg(body.size());
            connection->write((header+body).toLocal8Bit());
            return;
        }

        const auto user = parameters.queryItemValue("name");
        const auto amount = parameters.queryItemValue("amount");

        if (amount.toInt() < 0)
        {
            const auto body = answerFailure.arg("invalid_amount");
            const auto header = headerOK.arg(body.size());
            connection->write((header+body).toLocal8Bit());
            return;
        }

        bool valid = false;
        QString error = "unknown_user";

        if (user == "Rich Guy")
        {
            if (amount.toInt() <= 4096)
                valid = true;
            else
                error = "insufficent_funds";
        }
        if (user == "Poor Guy")
        {
            if (amount.toInt() <= 1050)
                valid = true;
            else
                error = "insufficent_funds";
        }
        if (user == "Broke Bloke")
        {
            if (amount.toInt() == 0)
                valid = true;
            else
                error = "insufficent_funds";
        }

        const auto body = valid
                        ? withdrawAnswerSuccess.arg(user, amount)
                        : answerFailure.arg(error);
        const auto header = headerOK.arg(body.size());

        connection->write((header+body).toLocal8Bit());
        return;
    }

    const auto body = answerFailure.arg("not_found");
    const auto header = headerOK.arg(body.size());
    connection->write((header+body).toLocal8Bit());
    return;
}
