#include "Kick.hpp"

Kick::Kick(Client* origin, const std::string msg) :
AMessage(origin, "KICK", msg)
{
}

void	Kick::ExecuteCommand()
{
	std::cerr << "ASDDA" << std::endl;
}

Kick::~Kick()
{
}
