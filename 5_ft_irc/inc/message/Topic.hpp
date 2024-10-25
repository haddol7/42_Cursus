#pragma once

#include "AMessage.hpp"

class Topic : public AMessage
{
	public:
		Topic(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~Topic();

	private:
		Topic();
};
