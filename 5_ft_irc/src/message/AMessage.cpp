#include <sstream>

#include "Server.hpp"
#include "message/AMessage.hpp"
#include "message.hpp"

static std::string	FindCommand(const std::string& msg) // to indicate command of a message
{
	std::string::size_type	pos;
	std::string::size_type	end;

	if (msg[0] == ':')
	{
		pos = msg.find(' ');
		if (pos != std::string::npos)
			++pos;
	}
	else
		pos = 0;
	end = msg.find(' ', pos);

	if (end == std::string::npos)
		end = msg.find("\r\n");

	std::string	cmd;
	if (pos != std::string::npos)
		cmd = msg.substr(pos, end - pos);

	return cmd;
}

AMessage*	AMessage::GetMessageObject(Client* origin, const std::string& msg)
{
	const char* commandList[] = {"PASS", "NICK", "USER", "PRIVMSG", "JOIN", "INVITE", NULL}; // set accepting commands

	std::string cmd = FindCommand(msg); // to indicate command of a message

	size_t	index = 0;
	for (; commandList[index] != NULL; ++index)
	{
		if (cmd == commandList[index])
			break ;
	}

	int status = origin->GetRegisterStatus();
	if ((status != REGISTERD && !(index == PASS || index == NICK || index == USER)) || \
		(!(status & (1 << PASS)) && (index == NICK || index == USER)) )
	{
		return NULL;
	}

	switch (index)
	{
		case 0:
			return new Pass(origin, msg);
		case 1:
			return new Nick(origin, msg);
			break ;
		case 2:
			return new User(origin, msg);
			break ;
		case 3:
			return new Privmsg(origin, msg);
			break ;
		case 4:
			return new Join(origin, msg);
			break ;
		case 5:
			return new Invite(origin, msg);
			break;
		default:
			return NULL;
	}
}

const std::string& AMessage::GetPrefix() const
{
	return mPrefix;
}

const std::string& AMessage::GetMessagePrefix() const
{
	return mMessagePrefix;
}

const std::string&	AMessage::GetCommand() const
{
	return mCommand;
}


int	AMessage::GetParamCount() const
{
	return mParamCount;
}

void	AMessage::ParseMessage()
{
	std::string::size_type	pos;
	std::string::size_type	end;
	std::string::size_type	last;

	if (mBuff[0] == ':')
	{
		end = mBuff.find(" ");
		mMessagePrefix = mBuff.substr(0, end);
	}

	pos = mBuff.find(mCommand) + mCommand.length() + 1;
	last = mBuff.find("\r\n", pos);

	mParamCount = 0;
	end = mBuff.find(" ", pos);
	while (end != std::string::npos && end + 1 != last && mParamCount < 14)
	{
		mParamArray[mParamCount++] = mBuff.substr(pos, end - pos);
		pos = end + 1;
		end = mBuff.find(" ", pos);
	}
	if (end == std::string::npos)
		end = last;
	if (mParamCount != 14 || mBuff[pos] == ':')
		mParamArray[mParamCount++] = mBuff.substr(pos, end - pos);
}

AMessage::AMessage(Client* origin, const std::string& command, const std::string& msg) :
mOrigin(origin),
mCommand(command),
mBuff(msg)
{
	std::stringstream stream;

	stream	<< ":" << mOrigin->GetNickName() \
			<< "!" << mOrigin->GetHostName() \
            << "@" << mOrigin->GetIpAddressString() << " ";
	mPrefix = stream.str();

	ParseMessage();
}

AMessage::~AMessage()
{
}

void AMessage::ReplyToOrigin(const std::string& replymsg)
{
	std::string	result;

	result = Server::GetServer()->GetPrefix() + replymsg;
	Server::GetServer()->SendMessage(*mOrigin, result);
}
