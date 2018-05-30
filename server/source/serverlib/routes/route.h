#pragma once
#include <QJsonObject>
#include <QString>
#include <QWebSocket>

#include <network/request.h>

class RouteFactory
{
public:
    using Factory = void (RouteFactory::*)(QWebSocket*, const Request&);

    RouteFactory(QObject* server)
        : m_parent(server)
    {
        m_routes[""] = create<Overview>;
        m_routes["lobby"] = create<Lobby>;
        m_routes["game"] = create<Game>;
    }

    void handle(QWebSocket* socket)
    {
        auto request = Request::fromUrl(socket->resourceName());

        auto constructRoute = routeFactory(request.route);
        (this->*constructRoute)(socket, request);

        // TODO catch exceptions here
    }

protected:
    template <class Route>
    void create(QWebSocket* socket, const Request& request)
    {
        // TODO throw exceptions in here
        auto route = new Route(socket, request);
        route->setParent(m_parent);

        connect(socket, &QWebSocket::textMessageReceived, [socket](const QString& message) {
            const auto answer = handle(toJson(message));
            socket->sendTextMessage(toString(answer));
        });

        connect(socket, &QWebSocket::readChannelFinished, this, [this, socket] {
            disconnectClient(socket);
        });
    }

    void error(QWebSocket* socket, const Request& request)
    {
        // TODO throw exceptions in here
        const auto error = QString("Invalid Route: '%1'.").arg(request.route);
        socket->sendTextMessage(Route::toString(Route::generateError(error, Route::InvalidRoute)));
        socket->flush();
        socket->close();
        socket->deleteLater();
    }

    Factory routeFactory(const QString& routeName)
    {
        auto& route = m_routes.find(routeName);
        if (route == m_routes.end())
        {
            return error;
        }
        return route->second;
    }

    std::map<QString, Factory> m_routes;
    QObject* m_parent;
};

class Route : public QObject
{
public:
    Route();

    virtual void connectClient(QWebSocket* socket, const Request& request) = 0;

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

    static QJsonObject toJson(const QString& message);
    static QString toString(const QJsonObject& answer);

protected:
    static void disconnectClient(QWebSocket* socket);
};
