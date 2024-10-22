#pragma once

#include "AMessage.hpp"

class NoCommand : public AMessage
{
	public:
		NoCommand(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~NoCommand();

	private:
		NoCommand();
};
