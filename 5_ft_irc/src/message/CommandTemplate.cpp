#include "CommandTemplate.hpp"

/*
It is a Command class template.
Repace all occurance of 'CommandTemplate' to command name.
And implement its execution fuction.
*/

CommandTemplate::CommandTemplate(Client* origin, const std::string msg) :
AMessage(origin, "CommandTemplate", msg)
{
	//some work depending on command type
}

void	CommandTemplate::ExecuteCommand()
{
	//command execution depanding on command type
}

CommandTemplate::~CommandTemplate()
{
}
