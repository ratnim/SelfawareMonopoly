
#include <QTcpServer>
#include <QTcpSocket>

class MockCoinhiveServer
{

public:
    MockCoinhiveServer();

    ~MockCoinhiveServer();

protected:
    void connected();
    void reply(QTcpSocket * connection);

protected:
    QTcpServer m_tcpServer;

};
