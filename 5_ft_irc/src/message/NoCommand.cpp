#include "NoCommand.hpp"

NoCommand::NoCommand(const std::string nick, const std::string msg) :
AMessage(nick, "NoCommand", msg)
{
	//some work depending on command type
}

void	NoCommand::ExecuteCommand() const
{
	//command execution depanding on command type
}

NoCommand::~NoCommand()
{
}
