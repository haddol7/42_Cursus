#pragma once

#include "AMessage.hpp"

class Nick : public AMessage
{
	public:
		Nick(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~Nick();

	private:
		Nick();

		//Nickname validation check
		bool	isNickInvalid() const;
		bool	isNickDuplicated() const;

		//Error reply
		void	errorNoNick() const;
		void	errorErroneusNick() const;
		void	errorNickInUse() const;

	private:
		std::string	mNick;
};
