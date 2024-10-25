#include "Mode.hpp"

//TODO : Target에 닉네임이 들어왔을 때 무시
Mode::Mode(Client* origin, const std::string msg) :
	AMessage(origin, "MODE", msg),
	mParamIter(2)
{
	mTarget = mParamArray[0];
	mModeList = mParamArray[1];
}

void	Mode::ExecuteCommand()
{
	if (CheckParamAndGiveInfo() == false)
	{
		return ;
	}
	ExecuteAllLoop();
	if (mReplyParam.str().empty() == false)
	{
		SendReply();
	}
}

bool	Mode::CheckParamAndGiveInfo()
{
	if ((mTarget.empty() && mModeList.empty()))
	{
		ReplyToOrigin(ERR_NEEDMOREPARAMS("MODE"));
		return (false);
	}
	if (FindChannel() == false)
	{
		ReplyToOrigin(ERR_NOSUCHCHANNEL(mTarget));
		return (false);
	}
	if (mParamCount == mModeList.empty())
	{
		ReplyToOrigin(RPL_CHANNELMODEIS(mTarget, GetModeString()));
		return (false);
	}
	if (mChannel->IsOperator(*mOrigin) == false)
	{
		ReplyToOrigin(ERR_CHANOPRIVSNEEDED(mTarget));
		return (false);
	}
	return (true);
}

bool Mode::FindChannel()
{
	std::map<const std::string, Channel> &channel_map = Server::GetServer()->GetChannelList();
	std::map<const std::string, Channel>::iterator iter;

	iter = channel_map.find(mTarget);
	if (iter == channel_map.end())
	{
		return (false);
	}
	mChannel = &iter->second;
	return (true);
}

void Mode::ExecuteAllLoop()
{
	char	mode;
	char	mode_i = 0;
	bool	status = TURN_ON;
	int		perior_status = -1;
	char	status_ch = '\0';
	bool	success;

	for (; mModeList[mode_i] != '\0'; ++mode_i)
	{	
		mode = mModeList[mode_i];
		success = false;
		if (mode == '+' || mode == '-')
		{
			if (mode_i == 0 || status != (mode == '+'))
			{	
				status_ch = mode;
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
			case '+':
			case '-':
				break;
			default:
				ReplyToOrigin(ERR_UNKNOWNMODE(mode, mTarget));
				break;
		}
		if (success == true)
		{
			if (status_ch != '\0' && status_ch != perior_status)
			{
				mReplyParam << status_ch;
				perior_status = status_ch;
			}
			status_ch = '\0';
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
	if (mChannel->GetOneModeStatus(L_MODE) == mode && mode == TURN_OFF)
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
	else if (mChannel->GetLimit() == atoi(num.c_str()))
	{
		return (false);
	}
	else
	{
		mChannel->SetLimit(atoi(num.c_str()));
		mReplyParamValues << " " << mChannel->GetLimit();
	}
	mChannel->ToggleModeStatus(L_MODE, mode);
	return (true);
}

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
	if (Server::GetServer()->ReturnClientOrNull(client) == NULL)
	{
		ReplyToOrigin(ERR_NOSUCHNICK(client));
		return (false);
	}
	const Client *client_target = mChannel->FindUser(client);
	if (client_target == NULL)
	{
		return (false);
	}
	bool isOper = mChannel->IsOperator(*client_target);
	if (mode == isOper)
	{
		return (false);
	}
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

void Mode::SendReply() const
{
	std::stringstream	resultstream;
	std::string			result;

	resultstream << GetPrefix() << "MODE " << mTarget << " " << mReplyParam.str() << mReplyParamValues.str() << "\r\n";
	result = resultstream.str();
	result.insert(result.rfind(" ") + 1, ":");
	mChannel->SendBackCmdMsg(result);
}

const std::string Mode::GetModeString() const
{
	std::string			result;
	std::stringstream	modestream;
	std::stringstream	paramstream;

	modestream << "+";
	if (mChannel->GetOneModeStatus(I_MODE))
	{
		modestream << "i";
	}
	if (mChannel->GetOneModeStatus(K_MODE))
	{
		modestream << "k";
		if (mChannel->IsOperator(*mOrigin) == false)
		{
			paramstream << " <key>";
		}
		else
		{
			paramstream << " " << mChannel->GetKey();
		}
	}
	if (mChannel->GetOneModeStatus(L_MODE))
	{
		modestream << "l";
		paramstream << " " << mChannel->GetLimit();
	}
	if (mChannel->GetOneModeStatus(T_MODE))
	{
		modestream << "t";
	}
	result = modestream.str() + paramstream.str();
	result.insert(result.rfind(" ") + 1, ":");
	return (result);
}

Mode::~Mode()
{
}
