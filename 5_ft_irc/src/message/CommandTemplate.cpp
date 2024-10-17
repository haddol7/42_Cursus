#include "CommandTemplate.hpp"

/*
It is a Command class template.
Repace all occurance of 'CommandTemplate' to command name.
And implement its execution fuction.
*/

CommandTemplate::CommandTemplate(const std::string nick, const std::string msg) :
AMessage(nick, "CommandTemplate", msg)
{
	//some work depending on command type
}

void	CommandTemplate::ExecuteCommand() const
{
	//command execution depanding on command type
}

CommandTemplate::~CommandTemplate()
{
}
