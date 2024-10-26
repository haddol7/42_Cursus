#pragma once

#include "AMessage.hpp"

class Ping : public AMessage
{
	public:
		Ping(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~Ping();

	private:
		Ping();

		std::string	mTarget;
		std::string	mServerName;
};
