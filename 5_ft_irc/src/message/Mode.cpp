#include "Mode.hpp"

/*
It is a Command class template.
Repace all occurance of 'Mode' to command name.
And implement its execution fuction.
*/

Mode::Mode(Client* origin, const std::string msg) :
AMessage(origin, "MODE", msg)
{
}

void	Mode::ExecuteCommand()
{
}

Mode::~Mode()
{
}
