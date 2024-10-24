#pragma once

#include <cstring>
#include <deque>
#include <iostream>
#include <sstream>
#include "AMessage.hpp"
#include "Channel.hpp"
#include "NewException.hpp"
#include "ReplyMacros.hpp"
#include "Server.hpp"

class Join : public AMessage
{
	public:
		/* exception class */
		class NoSuchChannelException : public NewException
		{
			public :
				virtual	~NoSuchChannelException() throw();
				NoSuchChannelException(const std::string &channelName);
				virtual std::string	what() const throw();
			private :
				NoSuchChannelException();
				const std::string	mChannelName;
		};
		class TooManyChannelsException : public NewException
		{
			public :
				virtual	~TooManyChannelsException() throw();
				TooManyChannelsException(const std::string &channelName);
				virtual std::string	what() const throw();
			private :
				TooManyChannelsException();
				const std::string	mChannelName;
		};
		class NeedMoreParamException : public NewException
		{
			public :
				virtual	~NeedMoreParamException() throw();
				virtual std::string	what() const throw();
		};
		class ChannelIsFullException : public NewException
		{
			public :
				virtual	~ChannelIsFullException() throw();
				ChannelIsFullException(const std::string &channelName);
				virtual std::string	what() const throw();
			private :
				ChannelIsFullException();
				const std::string	mChannelName;
		};
		class InviteOnlyChanException : public NewException
		{
			public :
				virtual	~InviteOnlyChanException() throw();
				InviteOnlyChanException(const std::string &channelName);
				virtual std::string	what() const throw();
			private :
				InviteOnlyChanException();
				const std::string	mChannelName;
		};
		class BannedFromChanException : public NewException
		{
			public :
				virtual	~BannedFromChanException() throw();
				BannedFromChanException(const std::string &channelName);
				virtual std::string	what() const throw();
			private :
				BannedFromChanException();
				const std::string	mChannelName;
		};
		class BadChannelKeyException : public NewException
		{
			public :
				virtual	~BadChannelKeyException() throw();
				BadChannelKeyException(const std::string &channelName);
				virtual std::string	what() const throw();
			private :
				BadChannelKeyException();
				const std::string	mChannelName;
		};


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
		bool				isControlCharInString(const std::string &s);
		bool				isChannelNameValid(const std::string &channelName);
		bool				isChannelKeyValid(const std::string &channelKey);
		std::string			getParameter();
		void				parseParameter(const std::string &parameter);
		std::string			GetJoinSendBack(const std::string &channelName);
		
		/* private member variable */
		// channel, key info
		std::deque<std::string>	mChannelList;
		std::deque<std::string>	mChannelKeyList;
};
