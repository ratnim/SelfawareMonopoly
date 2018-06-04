#pragma once
#include <QJsonObject>
#include <QString>
#include <QWebSocket>

#include <network/request.h>

class Route : public QObject
{
public:
    using ActionCallback = std::function<void(const QJsonValue&)>;

    Route(QWebSocket* socket);

    void incommingMessage(const QString& message);
    void disconnectClient();

protected:
    static QJsonObject toJson(const QString& message);
    ActionCallback actionHandler(const QString& name) const;

    QWebSocket* m_socket;
    std::map<QString, ActionCallback> m_actions;
};
