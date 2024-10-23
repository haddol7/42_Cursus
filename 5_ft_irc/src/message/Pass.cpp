#include "Pass.hpp"

Pass::Pass(Client* origin, const std::string msg) :
AMessage(origin, "PASS", msg)
{
	
}

void	Pass::ExecuteCommand()
{
	
}

Pass::~Pass()
{
}
