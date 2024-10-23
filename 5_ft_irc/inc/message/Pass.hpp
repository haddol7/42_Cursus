#pragma once

#include "AMessage.hpp"

class Pass : public AMessage
{
	public:
		Pass(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~Pass();

	private:
		std::string mPassword;
		Pass();
};
