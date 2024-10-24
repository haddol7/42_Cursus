#pragma once

#include "AMessage.hpp"

class Mode : public AMessage
{
	public:
		Mode(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~Mode();

	private:
		Mode();
};
