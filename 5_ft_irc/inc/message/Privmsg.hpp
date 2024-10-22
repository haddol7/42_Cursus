#pragma once

#include "AMessage.hpp"

class Privmsg : public AMessage
{
	public:
		Privmsg(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~Privmsg();
		void ParseBuffer();

	private:
		Privmsg();
		std::string mTarget;
		std::string mMessage;
};
