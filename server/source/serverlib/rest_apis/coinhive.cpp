
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

const QString urlBegin("https://api.coinhive.com");
const size_t withdrawBlockSize(1024);

MiningSupervisor::MiningSupervisor(const size_t interval)
: m_timer()
{
    QObject::connect(&m_timer, &QTimer::timeout, this, &MiningSupervisor::onTimer);
    m_timer.start(interval * 1000);
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
        const auto blocks = balance / withdrawBlockSize;

        if (blocks < 1)
            break; // Others will only have lower balance

        const auto withdraw = blocks * withdrawBlockSize;

        auto reply = requestWithdraw(name, withdraw);
        QObject::connect(reply, &QNetworkReply::finished, [reply, this](){onWithdrawReply(reply);});
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
    const auto blocks = amount / withdrawBlockSize;

    emit userMined(name, blocks);
}

QNetworkReply * requestTop()
{
    static const auto env = QProcessEnvironment::systemEnvironment();
    static const auto secretKey = env.value("CoinhivePrivateKey", "");
    static bool warnedKey = false;

    if (secretKey.isEmpty() && !warnedKey)
    {
        qDebug() << "Coinhive secret key not provided";
        warnedKey = true;
    }

    QUrlQuery query;
    query.addQueryItem("secret", secretKey);
    query.addQueryItem("order", "balance");

    QUrl request(urlBegin + "/user/top");
    request.setQuery(query);

    return sendGET(request);
}

QNetworkReply * requestWithdraw(const QString& userName, const size_t amount)
{
    static const auto env = QProcessEnvironment::systemEnvironment();
    static const auto secretKey = env.value("CoinhivePrivateKey", "");
    static bool warnedKey = false;

    if (secretKey.isEmpty() && !warnedKey)
    {
        qDebug() << "Coinhive secret key not provided";
        warnedKey = true;
    }

    QUrlQuery query;
    query.addQueryItem("secret", secretKey);
    query.addQueryItem("name", userName);
    query.addQueryItem("amount", QString::number(amount));

    QUrl request(urlBegin + "/user/withdraw");
    request.setQuery(query);

    return sendPOST(request, QByteArray());
}

} // namespace coinhive

} // namespace rest_apis
