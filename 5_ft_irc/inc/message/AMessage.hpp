#pragma once

#include <string>

#include "ReplyMacros.hpp"

class Client;

class AMessage
{
	public:
		static const char*	commandList[];
		
		static AMessage*	GetMessageObject(Client* origin, const std::string& msg);
		const std::string&	GetPrefix() const;
		const std::string&	GetMessagePrefix() const;
		const std::string&	GetCommand() const;
		int					GetParamCount() const;
		void				ReplyToOrigin(const std::string& replymsg);
		void				ParseMessage();
		virtual void		ExecuteCommand() = 0;
		virtual 			~AMessage();


	protected:
		AMessage(Client* origin, const std::string& command, const std::string& msg);

	private:
		AMessage();

	protected:
		Client*		mOrigin;
		std::string mPrefix;
		std::string	mMessagePrefix;
		std::string	mCommand;
		std::string	mParamArray[15];
		int			mParamCount;
		std::string mBuff;
};

#include "Client.hpp"
