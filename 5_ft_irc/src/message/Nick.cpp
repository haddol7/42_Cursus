#include "Nick.hpp"

Nick::Nick(const std::string nick, const std::string msg) :
AMessage(nick, "Nick", msg)
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
