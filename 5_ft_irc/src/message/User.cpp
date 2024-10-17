#include "User.hpp"

User::User(const std::string nick, const std::string msg) :
AMessage(nick, "User", msg)
{
	//some work depending on command type
}

void	User::ExecuteCommand() const
{
	//command execution depanding on command type
}

User::~User()
{
}
