#include "Client.hpp"
#include "message/User.hpp"

User::User(Client* origin, const std::string msg) :
AMessage(origin, "User", msg)
{
	int	index = 0;
	while (mBuffArray[index] != "USER" && index < mParamCount)
		++index;

	switch (mParamCount - index)
	{
		case 5:
			mRealName = mBuffArray[index + 4];
			//FALLTHROUGH
		case 4:
			mServerName = mBuffArray[index + 3];
			//FALLTHROUGH
		case 3:
			mHostName = mBuffArray[index + 2];
			//FALLTHROUGH
		case 2:
			mUserName = mBuffArray[index + 1];
			//FALLTHROUGH
		default:
			;
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
