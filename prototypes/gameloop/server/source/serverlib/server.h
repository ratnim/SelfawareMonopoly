#pragma once

#include <QTcpServer>

#include <vector>

#include "event.h"
#include "gamestate.h"
#include "path.h"

class Server : public QTcpServer
{
public:
    Server();

    void run();

    static QString staticPage(const QString &filename);

protected:
    QTcpSocket* acccept();
    QByteArray handle(const QByteArray& data);
    void finish(QTcpSocket* socket, const QByteArray& data);

    QString handleLobby(const Request& request);
    QString handleGame(const Request& request);

    std::vector<Path> m_paths;
    std::vector<std::unique_ptr<Event>> m_events;
    GameState m_state;
};
