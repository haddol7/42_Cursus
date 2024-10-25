#include "Topic.hpp"

Topic::Topic(Client* origin, const std::string msg) :
AMessage(origin, "TOPIC", msg)
{
}

void	Topic::ExecuteCommand()
{
}

Topic::~Topic()
{
}
