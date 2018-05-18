#pragma once

#include <vector>

#include <QDir>
#include <QTcpServer>

class FileServer : public QTcpServer
{
public:
    FileServer(const QString& rootDirectory);

protected:
    QTcpSocket* acccept();
    void finish(QTcpSocket* socket, const QByteArray& data);

    QByteArray handle(const QString& data);
    QByteArray staticPage(const QString& filename);
    std::map<QString, QString> createRoutes();

    QDir m_rootDirectory;
};
