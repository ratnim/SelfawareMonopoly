
#include <QTcpServer>
#include <QTcpSocket>

class MockBasicRestServer
{

public:
    MockBasicRestServer();

    ~MockBasicRestServer();

protected:
    void connected();
    void reply(QTcpSocket * connection);

protected:
    QTcpServer m_tcpServer;

};
