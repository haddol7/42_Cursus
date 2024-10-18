#pragma once

#include "AMessage.hpp"

class NoCommand : public AMessage
{
	public:
		NoCommand(const std::string nick, const std::string msg);
		virtual void	ExecuteCommand() const;
		virtual	~NoCommand();

	private:
		NoCommand();
};
