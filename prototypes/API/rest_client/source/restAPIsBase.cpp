
#include <restAPIsBase.h>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QByteArray>

#include <QEventLoop>

namespace
{

QByteArray waitFor(QNetworkReply* reply)
{
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    
    auto replyContent = reply->readAll();
    
    reply->close();
    reply->deleteLater();
    
    return replyContent;
}

} // namespace

namespace rest_apis
{
QNetworkAccessManager manager;

QByteArray sendGET(const QUrl& url)
{
    auto reply = manager.get(QNetworkRequest(url));
    return waitFor(reply);
}

QByteArray sendDELETE(const QUrl& url)
{
    auto reply = manager.deleteResource(QNetworkRequest(url));
    return waitFor(reply);
}

QByteArray sendPOST(const QUrl& url, const QByteArray& data)
{
    auto reply = manager.post(QNetworkRequest(url), data);
    return waitFor(reply);
}

QByteArray sendPUT(const QUrl& url, const QByteArray& data)
{
    auto reply = manager.put(QNetworkRequest(url), data);
    return waitFor(reply);
}

} // namespace rest_apis
