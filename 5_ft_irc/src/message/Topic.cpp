#include "Topic.hpp"

Topic::Topic(Client* origin, const std::string msg) :
	AMessage(origin, "TOPIC", msg),
	mTargetChannel(mParamArray[0]),
	mTargetTopic(mParamArray[1])
{
	mOriginNick = mOrigin->GetNickName();
	if (mTargetTopic.empty() && mBuff.find(":") != std::string::npos)
	{
		mTargetTopic = ":";
	}
}

void Topic::ExecuteCommand()
{
	if (IsValidChannel() == false)
	{
		return ;
	}
	if (IsOperatorOrReplyInfo() == true)
	{
		return ;
	}
	SetTopic();
	SendReply();
}

bool Topic::IsValidChannel()
{
	if (mTargetChannel.empty())
	{
		ReplyToOrigin(ERR_NEEDMOREPARAMS("TOPIC"));
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

bool Topic::IsOperatorOrReplyInfo()
{
	if (mTargetTopic.empty())
	{
		std::string	current_topic = mChannel->GetTopic();
		if (current_topic.empty())
		{
			ReplyToOrigin(RPL_NOTOPIC(mTargetChannel));
			return (true);
		}
		ReplyToOrigin(RPL_TOPIC(mTargetChannel, current_topic));
		return (true);
	}
	if (mChannel->GetOneModeStatus(T_MODE) == TURN_ON && \
		mChannel->FindOpInChannelWithNick(mOriginNick) == NULL)
	{
		ReplyToOrigin(ERR_CHANOPRIVSNEEDED(mTargetChannel));
		return (true);
	}
	return (false);
}

void Topic::SetTopic()
{
	size_t	pos = mTargetTopic.find(":");

	if (pos == std::string::npos && mParamCount >= 3)
	{
		std::stringstream	joined_topic;
		for (int i = 2; i < mParamCount; ++i)
		{
			joined_topic << mParamArray[i];
			if (i + 1 < mParamCount)
			{
				joined_topic << " ";
			}
		}
		mTargetTopic = joined_topic.str();
	}
	else if (pos != std::string::npos)
	{
		mTargetTopic.erase(pos, 1);
	}
	mChannel->SetTopic(mTargetTopic);
}

void Topic::SendReply() const
{
	std::stringstream	resultstream;
	std::string			result;

	resultstream << GetPrefix() << "TOPIC " << mTargetChannel << " :" << mTargetTopic << "\r\n";
	result = resultstream.str();
	mChannel->SendBackCmdMsg(result);
}

bool Topic::FindChannel()
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

Topic::~Topic()
{
}
