#include <cctype>

#include "Server.hpp"
#include "ReplyMacros.hpp"
#include "Nick.hpp"

Nick::Nick(Client* origin, const std::string msg) :
AMessage(origin, "NICK", msg)
{
	if (mParamCount)
		mNick =	mParamArray[0];
}

void	Nick::ExecuteCommand()
{
	if (mNick.length() == 0)
		ReplyToOrigin(ERR_NONICKNAMEGIVEN);
	else if (isNickValid() == false)
		ReplyToOrigin(ERR_ERRONEUSNICKNAME(mNick));
	else if (isNickDuplicated() == true)
		ReplyToOrigin(ERR_NICKNAMEINUSE(mNick));
	else
	{
		mOrigin->SetNickName(mNick);
		mOrigin->TurnOnRegisterStatus(NICK);
	}
}

Nick::~Nick()
{
}

static bool	isCharacterAllowed(char c)
{
	if (std::isalnum(c))
		return true;
	else if ((c >= 0x5B && c <= 0x60) || (c >= 0x7B && c <= 0x7D) || c == '-')
		return true;
	return false;
}

bool	Nick::isNickValid() const
{
	if (mNick.length() > 9)
		return false;
	else if (std::isdigit(mNick[0]) || mNick[0] == '-')
		return false;
	for (unsigned int i = 0; i < mNick.length(); ++i)
	{
		if (isCharacterAllowed(mNick[i]) == false)
			return false;
	}
	return true;
}

bool	Nick::isNickDuplicated() const
{
	Server	*server = Server::GetServer();

	if (server->ReturnClientOrNull(mNick))
		return true;
	return false;
}
