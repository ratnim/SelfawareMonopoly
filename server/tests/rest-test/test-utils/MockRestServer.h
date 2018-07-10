
#include <QTcpServer>
#include <QTcpSocket>

class MockRestServer
{

public:
    MockRestServer();

    ~MockRestServer();

protected:
    void connected();
    void reply(QTcpSocket * connection);

protected:
    QTcpServer m_tcpServer;

};
