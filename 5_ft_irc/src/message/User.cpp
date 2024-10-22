#include "User.hpp"

User::User(Client* origin, const std::string msg) :
AMessage(origin, "User", msg)
{
	//some work depending on command type
}

void	User::ExecuteCommand()
{
	//command execution depanding on command type
}

User::~User()
{
}
