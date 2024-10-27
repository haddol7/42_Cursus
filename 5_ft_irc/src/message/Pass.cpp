#include "Client.hpp"
#include "Pass.hpp"
#include "ReplyMacros.hpp"

Pass::Pass(Client* origin, const std::string msg) :
AMessage(origin, "PASS", msg)
{
}

void	Pass::ExecuteCommand()
{
	if (mParamCount == 0)
	{
		ReplyToOrigin(ERR_NEEDMOREPARAMS("PASS"));
		return ;
	}
	if (mOrigin->GetRegisterStatus() == REGISTERD)
	{
		ReplyToOrigin(ERR_ALREADYREGISTRED);
		return ;
	}
	mPassword = mParamArray[0];
	if (mPassword == Server::GetServer()->GetPassword())
	{
		mOrigin->TurnOnRegisterStatus(PASS);
	}
}

Pass::~Pass()
{
}
