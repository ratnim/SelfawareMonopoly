#pragma once

#include <QTcpServer>

class Server : public QTcpServer
{
public:
    Server();

    void run();

protected:
    QTcpSocket* acccept();
    QByteArray handle(const QByteArray& data);
    void finish(QTcpSocket* socket, const QByteArray& data);
};
