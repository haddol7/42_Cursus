#include "NoCommand.hpp"

NoCommand::NoCommand(Client* origin, const std::string msg) :
AMessage(origin, "NoCommand", msg)
{
	//some work depending on command type
}

void	NoCommand::ExecuteCommand()
{
	//command execution depanding on command type
}

NoCommand::~NoCommand()
{
}
