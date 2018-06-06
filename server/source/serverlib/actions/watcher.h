#pragma once

#include <QJsonValue>
#include <QObject>

class Watcher : public QObject
{
    Q_OBJECT

public:
    Watcher(QObject* object = nullptr);

signals:
    void send(const QString& message);
};
