#include "Part.hpp"

Part::Part(Client* origin, const std::string msg) :
	AMessage(origin, "PART", msg),
	mTargetChannel(mParamArray[0]),
	mTargetMsg(mParamArray[1]),
	mOriginNick(mOrigin->GetNickName())
{
	if (mTargetMsg.empty())
	{
		mTargetMsg = mOriginNick;
	}
}

void Part::ExecuteCommand()
{
	if (IsValidChannel() == false)
	{
		return ;
	}
	SendReply();
	mChannel->RemoveOne(*mOrigin);
}

bool Part::IsValidChannel()
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
	if (mChannel->FindUser(mOriginNick) == NULL)
	{
		ReplyToOrigin(ERR_NOTONCHANNEL(mTargetChannel));
		return (false);
	}
	return (true);
}

bool Part::FindChannel()
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

//PART #twilight_zone
//:WiZ!jto@tolsun.oulu.fi PART #playzone :I losts
void Part::SendReply() const
{
	std::stringstream	resultstream;
	std::string			result;

	resultstream << GetPrefix() << "PART " << mTargetChannel << " :" << mTargetMsg << "\r\n";
	result = resultstream.str();
	mChannel->SendBackCmdMsg(result);
}

Part::~Part()
{
}
