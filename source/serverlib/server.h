#pragma once

#include <QMap>
#include <QScopedPointer>
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

protected:
    QTcpSocket* acccept();
    QByteArray handle(const QString& data);
    void finish(QTcpSocket* socket, const QByteArray& data);

    GameState m_state;
};
