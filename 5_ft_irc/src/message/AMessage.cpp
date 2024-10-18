#include "message/AMessage.hpp"
#include "message.hpp"

std::string	FindCommand(std::string msg) // to indicate command of a message
{
	std::string::size_type	pos;
	std::string::size_type	end;

	if (msg[0] == ':')
		pos = msg.find(' ') + 1;
	else
		pos = 0;
	end = msg.find(' ', pos);

	std::string	cmd;
	cmd.append(msg, pos, end - pos);

	return cmd;
}

AMessage*	AMessage::GetMessageObject(const std::string nick, const std::string msg)
{
	const char* commandList[] = {"NICK", "USER"}; // set accepting commands

	std::string cmd = FindCommand(msg); // to indicate command of a message
	int	index = 0;
	for (; commandList[index]; ++index)
	{
		if (msg == commandList[index])
			break ;
	}

	AMessage*	message;
	switch (index)
	{
		case 0:
			message = new Nick(nick, msg);
			break ;
		case 1:
			message = new User(nick, msg);
			break ;
		default:
			message = new NoCommand(nick, msg);
	}
	return message;
}

const std::string&	AMessage::GetOriginNick() const
{
	return mOriginNick;
}

const std::string&	AMessage::GetCommand() const
{
	return mCommand;
}

AMessage::AMessage(const std::string nick, const std::string command, const std::string msg) :
mOriginNick(nick),
mCommand(command),
mBuff(msg)
{
}

AMessage::~AMessage()
{
}
