#include "Part.hpp"


Part::Part(Client* origin, const std::string msg) :
AMessage(origin, "PART", msg)
{
}

void	Part::ExecuteCommand()
{
}

Part::~Part()
{
}
