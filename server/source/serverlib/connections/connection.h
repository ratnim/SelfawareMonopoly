#pragma once

#include <functional>

#include <QJsonObject>
#include <QWebSocket>

#include <watchers/watcher.h>
#include <network/connectionrequest.h>

class Connection : public Watcher
{
public:
    using RequestCallback = std::function<void(const QJsonValue&)>;

    Connection(QWebSocket* parent);

    void incommingMessage(const QString& message);
    static QJsonObject toJson(const QString& message);

protected:
    RequestCallback requestHandler(const QString& name) const;

    std::map<QString, RequestCallback> m_requests;
};
