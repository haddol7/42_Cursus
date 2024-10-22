#pragma once

#include "AMessage.hpp"

class Privmsg : public AMessage
{
	public:
		Privmsg(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~Privmsg();
		void	ParseBuffer();
		void	SendMessageClient();
		void	SendMessageChannel();
		void	SendPrivMessage(Client *target);

	private:
		Privmsg();
		std::string mTarget;
		std::string mMessage;
};
