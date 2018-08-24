#include "possiblerequest.h"

PossibleRequest::PossibleRequest(const QString& request, const QJsonObject data)
	: m_request(request), m_data(data)
{
}

QJsonObject PossibleRequest::toJson() const
{
    QJsonObject request;
    request["request"] = m_request;
    request["data"] = m_data;
    return request;
}

PossibleRequest PossibleRequest::playerReady()
{
    return PossibleRequest("player_ready");
}

PossibleRequest PossibleRequest::gameStart()
{
    return PossibleRequest("game_start");
}
