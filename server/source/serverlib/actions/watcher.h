#pragma once

#include <QJsonValue>
#include <QObject>

class Watcher : public QObject
{
    Q_OBJECT

signals:
    void send(const QString& message);
};
