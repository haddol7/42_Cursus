#pragma once

#include "AMessage.hpp"

class Nick : public AMessage
{
	public:
		Nick(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~Nick();

	private:
		Nick();
};
