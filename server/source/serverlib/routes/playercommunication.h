#pragma once
#include <QJsonObject>
#include <QString>
#include <QWebSocket>

#include <network/request.h>

class PlayerCommunication : public QObject
{
public:
    using Action = std::function<QString(const QJsonValue&)>;

    PlayerCommunication(QWebSocket* socket);

    void incommingMessage(const QString& message);

    // MOVE TO ERROR OBJECT
    enum error
    {
        NoError = 0,
        InvalidRoute,
        UnsupportedAction,
        MalformedRequest,
        InvalidRequest,
        InternalError,
    };
    static QJsonObject generateError(const QString& message, error code);
    // END MOVE

    // MOVE TO DIFFERENT POSITION
    static QJsonObject toJson(const QString& message);
    static QString toString(const QJsonObject& answer);
    // END MOVE

protected:
    void disconnectClient();

    QWebSocket* m_socket;
    std::map<QString, Action> m_actions;
};
