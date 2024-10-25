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
	std::map<const std::string, Channel> &channel_map = Server::GetServer()->GetChannelList();
	std::map<const std::string, Channel>::iterator it = channel_map.find(mTarget);	
	
	if (it == channel_map.end())
	{
		ReplyToOrigin(ERR_NOSUCHCHANNEL(mTarget));
		return;
	}
	Channel &channel = it->second;
	if (channel.FindUser(mOrigin->GetNickName()) == NULL)
	{
		ReplyToOrigin(ERR_CANNOTSENDTOCHAN(mTarget));
		return;
	}
	std::string	result;
	result = GetPrefix() + mBuff;
	channel.SendPrivateMsgToChannel(*mOrigin, result);
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

	result = GetPrefix() + mBuff;
	Server::GetServer()->SendMessage(*target, result);
}
