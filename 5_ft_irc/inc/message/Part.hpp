#pragma once

#include "AMessage.hpp"

class Part : public AMessage
{
	public:
		Part(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~Part();

	private:
		Part();
};
