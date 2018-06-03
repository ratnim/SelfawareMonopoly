#pragma once

#include <routes/route.h>
#include <actions/createaccount.h>

class OverviewRoute : public Route
{
public:
    OverviewRoute(QWebSocket* socket, const Request& request);

protected:
    CreateAccount m_createAccount;
};
