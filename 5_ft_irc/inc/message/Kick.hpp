#pragma once

#include "AMessage.hpp"

class Kick : public AMessage
{
	public:
		Kick(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~Kick();

	private:
		Kick();
};
