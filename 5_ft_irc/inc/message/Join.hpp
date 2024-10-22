#pragma once

#include <cstring>
#include <deque>
#include <iostream>
#include <sstream>
#include "AMessage.hpp"
#include "Channel.hpp"
#include "Server.hpp"

class Join : public AMessage
{
	public:
		/* constructor && destructor */
		Join(Client* origin, const std::string &msg);
		virtual	~Join();

		/* public member function*/
		// excute command
		virtual void	ExecuteCommand();

	private:
		/* Join must not be called with default constructor(instance needs param) */
		Join();

		/* private member function */
		// parse parameter from msg
		const std::string	&getParameter();
		void				parseParameter(const std::string &parameter);
		
		/* private member variable */
		std::deque<std::string>	mChannelList;
		std::deque<std::string>	mChannelKeyList;
};
