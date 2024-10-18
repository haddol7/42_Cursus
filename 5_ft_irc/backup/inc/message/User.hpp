#pragma once

#include "AMessage.hpp"

class User : public AMessage
{
	public:
		User(const std::string nick, const std::string msg);
		virtual void	ExecuteCommand() const;
		virtual	~User();

	private:
		User();
};
