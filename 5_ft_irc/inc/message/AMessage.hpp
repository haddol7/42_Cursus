#pragma once

#include <string>

class AMessage
{
	public:
		static AMessage*	GetMessageObject(const std::string nick, const std::string msg);
		const std::string&	GetOriginNick() const;
		const std::string&	GetCommand() const;
		virtual void		ExecuteCommand() const = 0;
		virtual ~AMessage();

	protected:
		AMessage(const std::string nick, const std::string command, const std::string msg);

	private:
		AMessage();

	protected:
		std::string	mOriginNick;
		std::string	mCommand;
		std::string	mBuff;
};
