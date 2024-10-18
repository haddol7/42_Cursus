#pragma once

#include "AMessage.hpp"

class Nick : public AMessage
{
	public:
		Nick(const std::string nick, const std::string msg);
		virtual void	ExecuteCommand() const;
		virtual	~Nick();

	private:
		Nick();
};
