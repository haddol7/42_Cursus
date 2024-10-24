#include "Mode.hpp"

Mode::Mode(Client* origin, const std::string msg) :
AMessage(origin, "MODE", msg),
mParamIter(2)
{
	mTarget = mParamArray[0];
	mModeList = mParamArray[1];
}

void	Mode::ExecuteCommand()
{
	if ((mTarget.empty() && mModeList.empty()))
	{
		ReplyToOrigin(ERR_NEEDMOREPARAMS("MODE"));
		return ;
	}
	if (FindChannel() == false)
	{
		return ;
	}
	// TODO : 모드 응답 기능
	// key 값을 그냥 보여준다고??
	// if (mParamCount == mModeList.empty())
	// {
	// 	ReplyToOrigin(RPL_CHANNELMODEIS());
	// 	return ;
	// }
	if (mChannel->IsOperator(*mOrigin) == false)
	{
		ReplyToOrigin(ERR_CHANOPRIVSNEEDED(mTarget));
		return ;
	}
	ExecuteAllLoop();
	SendReply();
}

void Mode::SendReply() const
{
	std::stringstream	resultstream;
	std::string			result;

	resultstream << GetPrefix() << "MODE " << mTarget << " " << mReplyParam.str() << mReplyParamValues.str() << "\r\n";
	result = resultstream.str();
	if (mReplyParamValues.str().empty() == false)
	{
		size_t pos = result.rfind(" ");
		result.insert(pos + 1, ":");
	}
	mChannel->SendBackCmdMsg(result);
}

bool Mode::FindChannel()
{
	std::map<const std::string, Channel> &channel_map = Server::GetServer()->GetChannelList();
	std::map<const std::string, Channel>::iterator iter;

	iter = channel_map.find(mTarget);
	if (iter == channel_map.end())
	{
		ReplyToOrigin(ERR_NOSUCHCHANNEL(mTarget));
		return (false);
	}
	mChannel = &iter->second;
	return (true);
}

void Mode::ExecuteAllLoop()
{
	bool	status = TURN_ON;
	char	mode;
	char	insert_plus_minus = '\0';
	bool	success;

	for (int mode_iter = 0; mModeList[mode_iter] != '\0'; ++mode_iter)
	{	
		mode = mModeList[mode_iter];
		success = false;

		if (mode == '+' || mode == '-')
		{
			if (mode_iter == 0 || status != (mode == '+'))
			{	
				insert_plus_minus = mode;
				status = (mode == '+') ? TURN_ON : TURN_OFF;
				continue;
			}
		}
		switch (mode)
		{
			case 'i':
				success = Execute_i(status);
				break;
			case 'k':
				success = Execute_k(mParamArray[mParamIter], status);
				break;
			case 'l':
				success = Execute_l(mParamArray[mParamIter], status);
				break;
			case 't':
				success = Execute_t(status);
				break;
			case 'o':
				success = Execute_o(mParamArray[mParamIter], status);
				break;
			default:
				ReplyToOrigin(ERR_UNKNOWNMODE(mode));
				break;
		}
		if (success == true)
		{
			if (insert_plus_minus != '\0')
			{
				mReplyParam << insert_plus_minus;
			}
			insert_plus_minus = '\0';
			mReplyParam << mode;
		}
	}
}

bool	Mode::Execute_i(bool mode)
{
	if (mChannel->GetOneModeStatus(I_MODE) == mode)
	{
		return (false);
	}
	return (mChannel->ToggleModeStatus(I_MODE, mode));
}

bool	Mode::Execute_k(const std::string& key, bool mode)
{	
	if (key.empty() == false)
	{
		mParamIter++;
	}
	if (mChannel->GetOneModeStatus(K_MODE) == mode)
	{
		return (false);
	}
	if (key.empty())
	{
		ReplyToOrigin(ERR_NEEDMOREPARAMS("k"));
		return (false);
	}
	if (mode == TURN_OFF && key != mChannel->GetKey())
	{
		return (false);
	}
	mChannel->SetKey(key);
	mReplyParamValues << " " << key;
	return (mChannel->ToggleModeStatus(K_MODE, mode));
}

bool	Mode::Execute_l(const std::string& num, bool mode)
{
	if (mode == TURN_ON && num.empty() == false)
	{
		mParamIter++;
	}
	if (mChannel->GetOneModeStatus(L_MODE) == mode)
	{
		return (false);
	}
	if (mode == TURN_OFF)
	{
		mChannel->SetLimit(LIMIT_OFF);
	}
	else if (num.empty())
	{
		ReplyToOrigin(ERR_NEEDMOREPARAMS("l"));
		return (false);
	}
	else
	{
		mChannel->SetLimit(atoi(num.c_str()));
		mReplyParamValues << " " << mChannel->GetLimit();
	}
	return (mChannel->ToggleModeStatus(L_MODE, mode));
}

//TODO : 껐다 키면 토픽이 제대로 있는지
bool	Mode::Execute_t(bool mode)
{
	if (mChannel->GetOneModeStatus(T_MODE) == mode)
	{
		return (false);
	}
	return (mChannel->ToggleModeStatus(T_MODE, mode));
}

bool	Mode::Execute_o(const std::string& client, bool mode)
{
	if (client.empty())
	{	
		ReplyToOrigin(ERR_NEEDMOREPARAMS("o"));
		return (false);
	}
	mParamIter++;
	const Client *client_target = mChannel->FindUser(client);
	if (client_target == NULL)
	{
		ReplyToOrigin(ERR_USERNOTINCHANNEL(client, mTarget));
		return (false);
	}

	//TODO : 이미 있는 사람이라면??
	//TODO : 없는 사람이라면?
	if (mode == TURN_ON)
	{
		mChannel->AddOperator(*client_target);
	}
	else
	{
		mChannel->DemoteOperator(*client_target);
	}
	mReplyParamValues << " " << client;
	return (true);
}

Mode::~Mode()
{
}
