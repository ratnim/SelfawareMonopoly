
#include <coinhive.h>

#include <restAPIsBase.h>

#include <QUrl>
#include <QUrlQuery>

namespace rest_apis
{

namespace coinhive
{

const QString urlBegin("https://api.coinhive.com");

QJsonDocument balance(const QString& secret, const QString& name)
{
    QUrlQuery query;
    query.addQueryItem("secret", secret);
    query.addQueryItem("name", name);

    QUrl request(urlBegin + "/user/balance");
    request.setQuery(query);

    auto response = sendGET(request);

    return QJsonDocument::fromJson(response);
}

} // namespace coinhive

} // namespace rest_apis
