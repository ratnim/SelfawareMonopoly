#pragma once

#include <functional>

#include <QJsonObject>
#include <QWebSocket>

#include <watchers/watcher.h>
#include <network/request.h>

class Connection : public Watcher
{
public:
    using ActionCallback = std::function<void(const QJsonValue&)>;

    Connection(QWebSocket* parent);

    void incommingMessage(const QString& message);
    static QJsonObject toJson(const QString& message);

protected:
    ActionCallback actionHandler(const QString& name) const;

    std::map<QString, ActionCallback> m_actions;
};
