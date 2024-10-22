#include <cctype>

#include "Server.hpp"
#include "ReplyMacros.hpp"
#include "Nick.hpp"

Nick::Nick(Client* origin, const std::string msg) :
AMessage(origin, "Nick", msg)
{
	std::string::size_type	pos;

	pos = mBuff.find("NICK");
	pos = mBuff.find(" ", pos);

	// if (pos != std::string::npos && ++pos != mBuff.length())
	// 	mNick.append(mBuff, pos, mBuff.length() - 1 - pos);
	// pos = mBuff.find(" ");
	mNick = mBuff.substr(pos + 1, mBuff.length() - 7);
	//TODO : 예외 상황 체크
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

static bool	checkLetter(char c)
{
	if (std::isalnum(c))
		return 0;
	else if ((c >= 0x5B && c <= 0x60) || (c >= 0x7B && c <= 0x7D) || c == '-')
		return 0;
	return 1;
}

bool	Nick::isNickInvalid() const
{
	if (mNick.length() > 9)
		return 1;
	else if (std::isdigit(mNick[0]) || mNick[0] == '-')
		return 1;
	for (unsigned int i = 0; i < mNick.length(); ++i)
	{
		if (checkLetter(mNick[i]))
			return 1;
	}
	return 0;
}

bool	Nick::isNickDuplicated() const
{
	Server	*server = Server::GetServer();
	Client	*client = server->ReturnClientOrNull(mNick);

	if (client == NULL)
		return false;
	return true;
}
