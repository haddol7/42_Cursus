#include "Server.hpp"
#include "Ping.hpp"

Ping::Ping(Client* origin, const std::string msg) :
AMessage(origin, "PING", msg)
{
	mServerName = Server::GetServer()->GetName();
	if (mParamCount > 0)
		mTarget = mParamArray[0];
}

void	Ping::ExecuteCommand()
{
	if (mTarget == mServerName)
	{
		Server*	server = Server::GetServer();
		std::string PongMessage;
		PongMessage = ":" + mServerName + " PONG " \
					  + mServerName + " :" + mServerName + "\r\n";
		server->SendMessage(*mOrigin, PongMessage);
	}
}

Ping::~Ping()
{
}
