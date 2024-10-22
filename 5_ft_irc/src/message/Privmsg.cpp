#include "Privmsg.hpp"

Privmsg::Privmsg(Client* origin, const std::string msg) :
AMessage(origin, "Privmsg", msg)
{
}

Privmsg::~Privmsg()
{
}

void Privmsg::ExecuteCommand()
{
	ParseBuffer();
}

void Privmsg::ParseBuffer()
{
	size_t		delim;
	std::string	msg_only_param;


	delim = mBuff.find(" ");
	msg_only_param = mBuff.substr(delim, mBuff.length());
	delim = msg_only_param.find(" :");
	if (delim == std::string::npos)
	{
		mTarget = msg_only_param;
		return ;
	}
	mTarget = msg_only_param.substr(0, delim);
	mMessage = msg_only_param.substr(delim + 1, msg_only_param.length());
}
