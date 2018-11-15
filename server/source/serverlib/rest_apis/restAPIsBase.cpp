
#include <rest_apis/restAPIsBase.h>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QByteArray>

#include <QEventLoop>


namespace rest_apis
{
QNetworkAccessManager manager;

QNetworkReply * sendGET(const QUrl& url)
{
    return manager.get(QNetworkRequest(url));
}

QNetworkReply * sendDELETE(const QUrl& url)
{
    return manager.deleteResource(QNetworkRequest(url));
}

QNetworkReply * sendPOST(const QUrl& url, const QByteArray& data)
{
    return manager.post(QNetworkRequest(url), data);
}

QNetworkReply * sendPUT(const QUrl& url, const QByteArray& data)
{
    return manager.put(QNetworkRequest(url), data);
}

} // namespace rest_apis
