#pragma once

#include "AMessage.hpp"

class User : public AMessage
{
	public:
		User(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~User();

	private:
		User();

		//<username> <hostname> <servername> :<realname>
		std::string	mUserName;
		std::string	mHostName;
		std::string	mServerName;
		std::string	mRealName;
};
