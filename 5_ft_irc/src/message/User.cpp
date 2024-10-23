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
	mOrigin->SetUserName(mUserName);
	mOrigin->SetHostName(mHostName);
	mOrigin->TurnOnRegisterStatus(USER);
}

User::~User()
{
}
