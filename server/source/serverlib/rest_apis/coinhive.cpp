
#include <rest_apis/coinhive.h>

#include <rest_apis/restAPIsBase.h>

#include <QUrl>
#include <QUrlQuery>
#include <QProcessEnvironment>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace rest_apis
{

namespace coinhive
{

MiningSupervisor::MiningSupervisor(const size_t interval, const size_t blockSize, const QString& host)
: m_timer()
, m_host(host)
, m_blockSize(blockSize)
{
    QObject::connect(&m_timer, &QTimer::timeout, this, &MiningSupervisor::onTimer);
    m_timer.start(interval * 1000);

    const auto env = QProcessEnvironment::systemEnvironment();
    const auto m_key = env.value("CoinhivePrivateKey", "");

    if (m_key.isEmpty())
    {
        qWarning() << "Coinhive secret key not provided. Requests will probably fail.";
    }
}

void MiningSupervisor::onTimer()
{
    auto reply = requestTop();
    QObject::connect(reply, &QNetworkReply::finished, [reply, this](){onTopReply(reply);});
}

void MiningSupervisor::onTopReply(QNetworkReply * reply)
{
    const auto json = QJsonDocument::fromJson(reply->readAll());

    if (!json.isObject())
    {
        qDebug() << "[coinhive] Received invalid JSON";
        return;
    }

    if (!json["success"].toBool())
    {
        qDebug() << "[coinhive] Error requesting top: " << json["error"].toString();
        return;
    }

    for (auto entry: json["users"].toArray())
    {
        const auto userObj = entry.toObject();
        const auto name = userObj["name"].toString();
        const auto balance = userObj["balance"].toInt();
        const auto blocks = balance / m_blockSize;

        if (blocks < 1)
            break; // Others will only have lower balance

        const auto withdraw = blocks * m_blockSize;

        auto request = requestWithdraw(name, withdraw);
        QObject::connect(request, &QNetworkReply::finished, [request, this](){onWithdrawReply(request);});
    }
}

void MiningSupervisor::onWithdrawReply(QNetworkReply * reply)
{
    const auto json = QJsonDocument::fromJson(reply->readAll());

    if (!json.isObject())
    {
        qDebug() << "[coinhive] Received invalid JSON";
        return;
    }

    if (!json["success"].toBool())
    {
        qDebug() << "[coinhive] Error requesting withdraw: " << json["error"].toString();
        return;
    }

    const auto name = json["name"].toString();
    const auto amount = json["amount"].toInt();
    const auto blocks = amount / m_blockSize;

    emit userMined(name, blocks);
}

QNetworkReply * MiningSupervisor::requestTop()
{
    QUrlQuery query;
    query.addQueryItem("secret", m_key);
    query.addQueryItem("order", "balance");

    QUrl request(m_host + "/user/top");
    request.setQuery(query);

    return sendGET(request);
}

QNetworkReply * MiningSupervisor::requestWithdraw(const QString& userName, const size_t amount)
{
    QUrlQuery query;
    query.addQueryItem("secret", m_key);
    query.addQueryItem("name", userName);
    query.addQueryItem("amount", QString::number(amount));

    QUrl request(m_host + "/user/withdraw");
    request.setQuery(query);

    return sendPOST(request, QByteArray());
}

} // namespace coinhive

} // namespace rest_apis
