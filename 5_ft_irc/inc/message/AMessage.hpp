#pragma once

#include <string>

#include "Client.hpp"

class AMessage
{
	public:
		static AMessage*	GetMessageObject(Client* origin, const std::string msg);
		const std::string&	GetCommand() const;
		const std::string&	GetPrefix() const;
		virtual void		ExecuteCommand() = 0;
		virtual ~AMessage();


	protected:
		AMessage(Client* origin, const std::string command, const std::string msg);

	private:
		AMessage();

	protected:
		Client*		mOrigin;
		std::string	mCommand;
		std::string	mBuff;
		std::string mPrefix;
};
