#pragma once

#include <string>

class Client;

class AMessage
{
	public:
		static AMessage*	GetMessageObject(Client* origin, const std::string& msg);
		const std::string&	GetCommand() const;
		const std::string&	GetPrefix() const;
		int					GetParamCount() const;
		void				ReplyToOrigin(const std::string& replymsg);
		void				ParseMessage(const std::string& msg);
		virtual void		ExecuteCommand() = 0;
		virtual 			~AMessage();


	protected:
		AMessage(Client* origin, const std::string& command, const std::string& msg);

	private:
		AMessage();

	protected:
		Client*		mOrigin;
		std::string	mCommand;
		std::string mPrefix;
		std::string mBuff; //compile error purpose, to be removed
		std::string	mBuffArray[17];
		int			mParamCount;
};

#include "Client.hpp"
