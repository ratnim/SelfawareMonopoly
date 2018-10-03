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

PossibleRequest PossibleRequest::rollDice()
{
    return PossibleRequest("roll_dice");
}

PossibleRequest PossibleRequest::endTurn()
{
    return PossibleRequest("end_turn");
}

PossibleRequest PossibleRequest::buyField()
{
	return PossibleRequest("buy_field");
}

PossibleRequest PossibleRequest::dontBuyField()
{
    return PossibleRequest("dont_buy_field");
}

PossibleRequest PossibleRequest::constructBuilding(const QJsonArray& groups)
{
    return PossibleRequest("construct_building", {{ "groups", groups }});
}

PossibleRequest PossibleRequest::payDebt(const QString& beneficiary, int amount)
{
    return PossibleRequest("pay_debt", { { "beneficiary", beneficiary } , { "amount" , amount } });
}
