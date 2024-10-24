#include "Client.hpp"
#include "message/User.hpp"

User::User(Client* origin, const std::string msg) :
AMessage(origin, "USER", msg)
{
	switch (mParamCount)
	{
		case 4:
			mRealName = mParamArray[3];
			//FALLTHROUGH
		case 3:
			mServerName = mParamArray[2];
			//FALLTHROUGH
		case 2:
			mHostName = mParamArray[1];
			//FALLTHROUGH
		case 1:
			mUserName = mParamArray[0];
			break ;
		default:
			break ;
	}
}

void	User::ExecuteCommand()
{
	// TODO : 임시 작업, 이후 자세한 예외 처리 등 필요!!
	if (mOrigin->GetRegisterStatus() & (1 << USER))
		ReplyToOrigin(ERR_ALREADYREGISTRED);
	else if (mParamCount < 4)
		ReplyToOrigin(ERR_NEEDMOREPARAMS(mCommand));
	else if (isParamAllowed() == false)
		return ;
	mOrigin->SetUserName(mUserName);
	mOrigin->SetHostName(mHostName);
	mOrigin->SetServerName(mServerName);
	mOrigin->SetRealName(mRealName);
	mOrigin->TurnOnRegisterStatus(USER);
}

static bool	isCharValid(const std::string& str, int lengthLimit)
{
	int	length = str.length();
	if (length > lengthLimit)
		return false;

	char	c;
	for (int i = 0; i < length; ++i)
	{
		c = str[i];
		if (c == '\0' || c == '\r' || c == '\n' || c == '@' || c == '!')
			return false;
	}
	return true;
}

bool	User::isParamAllowed() const
{
	if (isCharValid(mUserName, 16) == false)
		return false;
	else if (isCharValid(mHostName, 63) == false)
		return false;
	else if (isCharValid(mServerName, 32) == false)
		return false;
	else if (isCharValid(mRealName, 100) == false)
		return false;
	return true;
}

User::~User()
{
}
