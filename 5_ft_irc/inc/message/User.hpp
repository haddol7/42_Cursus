#pragma once

#include "AMessage.hpp"

class User : public AMessage
{
	public:
		User(Client* origin, const std::string msg);
		virtual void	ExecuteCommand() const;
		virtual	~User();

	private:
		User();
};
