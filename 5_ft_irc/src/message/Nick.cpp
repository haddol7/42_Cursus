#include "Nick.hpp"

Nick::Nick(Client* origin, const std::string msg) :
AMessage(origin, "Nick", msg)
{
	//some work depending on command type
}

void	Nick::ExecuteCommand() const
{
	//command execution depanding on command type
}

Nick::~Nick()
{
}
