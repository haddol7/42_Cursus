#include "Kick.hpp"

Kick::Kick(Client* origin, const std::string msg) :
	AMessage(origin, "KICK", msg),
	mTargetChannel(mParamArray[0]),
	mTargetClientStr(mParamArray[1]),
	mTargetReason(mParamArray[2]),
	mOriginNick(mOrigin->GetNickName())
{
}

void	Kick::ExecuteCommand()
{
	if (IsValidChannel() == false)
	{
		return ;
	}
	SendReply();
	mChannel->RemoveOne(*mTargetClientPtr);
}

bool Kick::IsValidChannel()
{
	if (mTargetChannel.empty())
	{
		ReplyToOrigin(ERR_NEEDMOREPARAMS("PART"));
		return (false);
	}
	if (FindChannel() == false)
	{
		ReplyToOrigin(ERR_NOSUCHCHANNEL(mTargetChannel));
		return (false);
	}
	if (Server::GetServer()->ReturnClientOrNull(mTargetClientStr) == NULL)
	{
		ReplyToOrigin(ERR_NOSUCHNICK(mTargetClientStr));
		return (false);
	}
	if (mChannel->FindUserInChannelWithNick(mOriginNick) == NULL)
	{
		ReplyToOrigin(ERR_NOTONCHANNEL(mTargetChannel));
		return (false);
	}
	mTargetClientPtr = mChannel->FindUserInChannelWithNick(mTargetClientStr);
	if (mTargetClientPtr == NULL)
	{
		ReplyToOrigin(ERR_USERNOTINCHANNEL(mTargetClientStr, mTargetChannel));
		return (false);
	}
	if (mChannel->FindOpInChannelWithNick(mOriginNick) == NULL)
	{		
		ReplyToOrigin(ERR_CHANOPRIVSNEEDED(mTargetChannel));
		return (false);
	}
	return (true);
}

bool Kick::FindChannel()
{
	std::map<const std::string, Channel> &channel_map = Server::GetServer()->GetChannelList();
	std::map<const std::string, Channel>::iterator iter;

	iter = channel_map.find(mTargetChannel);
	if (iter == channel_map.end())
	{
		return (false);
	}
	mChannel = &iter->second;
	return (true);
}

void Kick::SendReply() const
{
	std::stringstream	resultstream;
	std::string			result;

	resultstream << GetPrefix() << "KICK " << mTargetChannel << " " << mTargetClientStr;
	if (mTargetReason.empty())
	{
		resultstream << "\r\n";
	}
	else
	{
		resultstream <<  " :" << mTargetReason << "\r\n";
	}
	result = resultstream.str();
	mChannel->SendBackCmdMsg(result);
}

Kick::~Kick()
{
}
