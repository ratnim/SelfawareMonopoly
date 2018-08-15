#pragma once

#include <functional>

#include <QJsonObject>
#include <QWebSocket>

#include <watchers/watcher.h>
#include <network/request.h>

class Route : public Watcher
{
public:
    using ActionCallback = std::function<void(const QJsonValue&)>;

    Route(QWebSocket* parent);

    void incommingMessage(const QString& message);

protected:
    static QJsonObject toJson(const QString& message);
    ActionCallback actionHandler(const QString& name) const;

    std::map<QString, ActionCallback> m_actions;
};
