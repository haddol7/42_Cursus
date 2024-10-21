#include "message/AMessage.hpp"
#include "message.hpp"

std::string	FindCommand(std::string msg) // to indicate command of a message
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

	std::string	cmd;
	if (pos != std::string::npos && end != std::string::npos)
		cmd.append(msg, pos, end - pos);

	return cmd;
}

AMessage*	AMessage::GetMessageObject(Client* origin, const std::string msg)
{
	const char* commandList[] = {"NICK", "USER"}; // set accepting commands

	std::string cmd = FindCommand(msg); // to indicate command of a message
	int	index = 0;
	for (; commandList[index]; ++index)
	{
		if (cmd == commandList[index])
			break ;
	}

	AMessage*	message;
	switch (index)
	{
		case 0:
			message = new Nick(origin, msg);
			break ;
		case 1:
			message = new User(origin, msg);
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

AMessage::AMessage(Client* origin, const std::string command, const std::string msg) :
mOrigin(origin),
mCommand(command),
mBuff(msg)
{
}

AMessage::~AMessage()
{
}
