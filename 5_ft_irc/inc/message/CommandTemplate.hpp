#pragma once

#include "AMessage.hpp"

class CommandTemplate : public AMessage
{
	public:
		CommandTemplate(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~CommandTemplate();

	private:
		CommandTemplate();
};
