#include <sstream>
#include <Server.hpp>
#include "message/AMessage.hpp"
#include "message.hpp"

static std::string	FindCommand(std::string msg) // to indicate command of a message
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

AMessage*	AMessage::GetMessageObject(Client* origin, const std::string msg)
{
	const char* commandList[] = {"PASS", "NICK", "USER", "PRIVMSG", NULL}; // set accepting commands

	std::string cmd = FindCommand(msg); // to indicate command of a message

	size_t	index = 0;
	for (; commandList[index] != NULL; ++index)
	{
		if (cmd == commandList[index])
			break ;
	}

	//PASS가 무조건 오도록
	int status = origin->GetRegisterStatus();
	if (status != REGISTERD && !(index == PASS || index == NICK || index == USER) || \
		!status & (1 << PASS)&& (index == NICK || index == USER) )
	{
		return NULL;
	}
	
	AMessage*	message;
	switch (index)
	{
		case 0:
			message = new Pass(origin, msg);
			break;
		case 1:
			message = new Nick(origin, msg);
			break ;
		case 2:
			message = new User(origin, msg);
			break ;
		case 3:
			message = new Privmsg(origin, msg);
			break ;
		default:
			message = new NoCommand(origin, msg);
	}
	return message;
}

const std::string&	AMessage::GetCommand() const
{
	return mCommand;
}

const std::string& AMessage::GetPrefix() const
{
	return (mPrefix);
}

//prefix -> ":root_!root@127.0.0.1 "
AMessage::AMessage(Client* origin, const std::string command, const std::string msg) :
mOrigin(origin),
mCommand(command),
mBuff(msg)
{
	std::stringstream stream;

	stream	<< ":" << mOrigin->GetNickName() \
			<< "!" << mOrigin->GetHostName() \
            << "@" << mOrigin->GetIpAddressString() << " ";
	mPrefix = stream.str();
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
