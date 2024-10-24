#include "ReplyMacros.hpp"
#include "Privmsg.hpp"
#include "Server.hpp"

Privmsg::Privmsg(Client* origin, const std::string msg) :
AMessage(origin, "Privmsg", msg)
{
}

Privmsg::~Privmsg()
{
}

void Privmsg::ExecuteCommand()
{
	ParseBuffer();
	if (mTarget[0] == ':')
	{	
		ReplyToOrigin(ERR_NORECIPIENT(mOrigin->GetNickName()));
		return ;
	}
	else if (mMessage.empty() == true)
	{
		ReplyToOrigin(ERR_NOTEXTTOSEN);
		return ;
	}
	if (mTarget[0] == '#')
	{
		SendMessageChannel();
	}
	else
	{
		SendMessageClient();
	}
}

void Privmsg::ParseBuffer()
{
	size_t		delim;
	std::string	msg_only_param;

	delim = mBuff.find(" ");
	msg_only_param = mBuff.substr(delim + 1, mBuff.length());
	delim = msg_only_param.find(" :");
	if (delim == std::string::npos)
	{
		mTarget = msg_only_param;
		return ;
	}
	mTarget = msg_only_param.substr(0, delim);
	mMessage = msg_only_param.substr(delim + 1, msg_only_param.length());
}

void Privmsg::SendMessageChannel()
{	
	// if (there is no channel)
	// {
	// 	ERR_NOSUCHNICK
	// }
	// else if (channel is not invited)
	// {
	// 	ERR_CANNOTSENDTOCHAN
	// }
}

void Privmsg::SendMessageClient()
{
	Client* target = Server::GetServer()->ReturnClientOrNull(mTarget);

	if (target == NULL)
	{
		ReplyToOrigin(ERR_NOSUCHNICK(mTarget));
		return ;
	}
	SendPrivMessage(target);
}

void Privmsg::SendPrivMessage(Client* target)
{
	std::string	result;

	result = GetPrefix() + mBuff + "\r\n";
	Server::GetServer()->SendMessage(*target, result);
}
