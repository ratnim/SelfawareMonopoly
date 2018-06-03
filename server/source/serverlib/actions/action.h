#pragma once

#include <QJsonValue>

#include <actions/watcher.h>

class Action : public Watcher
{
    Q_OBJECT

public:
    virtual void handle(const QJsonValue& data) = 0;
};
