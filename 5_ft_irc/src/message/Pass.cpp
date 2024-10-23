#include "Client.hpp"
#include "Pass.hpp"
#include "ReplyMacros.hpp"

Pass::Pass(Client* origin, const std::string msg) :
AMessage(origin, "PASS", msg)
{
}

void	Pass::ExecuteCommand()
{
	size_t	pos;

	pos = mBuff.rfind(" ");
	if (pos == std::string::npos)
	{
		ReplyToOrigin(ERR_NEEDMOREPARAMS("PASS"));
		return ;
	}
	if (mOrigin->GetRegisterStatus() == REGISTERD)
	{
		ReplyToOrigin(ERR_ALREADYREGISTRED);
		return ;
	}
	mPassword = mBuff.substr(pos + 1, mBuff.length() - 7);
	if (mPassword == Server::GetServer()->GetPassword())
	{
		mOrigin->TurnOnRegisterStatus(PASS);
	}
}

Pass::~Pass()
{
}
