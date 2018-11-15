
#pragma once

#include <QUrl>
#include <QByteArray>
#include <QNetworkReply>

namespace rest_apis
{

QNetworkReply * sendGET(const QUrl& url);
QNetworkReply * sendDELETE(const QUrl& url);

QNetworkReply * sendPOST(const QUrl& url, const QByteArray& data);
QNetworkReply * sendPUT(const QUrl& url, const QByteArray& data);

} // namespace rest_apis
