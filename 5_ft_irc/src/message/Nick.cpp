#include <cctype>

#include "Server.hpp"
#include "ReplyMacros.hpp"
#include "Nick.hpp"

Nick::Nick(Client* origin, const std::string msg) :
AMessage(origin, "Nick", msg)
{
	std::string::size_type	pos;
	std::string::size_type	end;

	pos = mBuff.find("NICK");
	pos = mBuff.find(" ", pos);

	end = mBuff.find("\r\n");

	if (pos != std::string::npos && ++pos != end)
		mNick = mBuff.substr(pos, end - pos);
}

void	Nick::ExecuteCommand()
{
	if (mNick.length() == 0)
		ReplyToOrigin(ERR_NONICKNAMEGIVEN);
	else if (isNickInvalid())
		ReplyToOrigin(ERR_ERRONEUSNICKNAME(mNick));
	else if (isNickDuplicated())
		ReplyToOrigin(ERR_NICKNAMEINUSE(mNick));
	else
		mOrigin->SetNickName(mNick);
}

Nick::~Nick()
{
}

static bool	isCharacterNotAllowed(char c)
{
	if (std::isalnum(c))
		return false;
	else if ((c >= 0x5B && c <= 0x60) || (c >= 0x7B && c <= 0x7D) || c == '-')
		return false;
	return true;
}

bool	Nick::isNickInvalid() const
{
	if (mNick.length() > 9)
		return true;
	else if (std::isdigit(mNick[0]) || mNick[0] == '-')
		return true;
	for (unsigned int i = 0; i < mNick.length(); ++i)
	{
		if (isCharacterNotAllowed(mNick[i]))
			return true;
	}
	return false;
}

bool	Nick::isNickDuplicated() const
{
	Server	*server = Server::GetServer();

	if (server->ReturnClientOrNull(mNick))
		return true;
	return false;
}
