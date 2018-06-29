
#pragma once

#include <QUrl>
#include <QByteArray>

namespace rest_apis
{

QByteArray sendGET(const QUrl& url);
QByteArray sendDELETE(const QUrl& url);

QByteArray sendPOST(const QUrl& url, const QByteArray& data);
QByteArray sendPUT(const QUrl& url, const QByteArray& data);

} // namespace rest_apis
