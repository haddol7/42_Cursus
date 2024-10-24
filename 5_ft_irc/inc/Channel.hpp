#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>

#include "Client.hpp"
#include "NewException.hpp"
#include "Server.hpp"
#include "ReplyMacros.hpp"

class Channel
{
public:
	// exception class
	class BadChannelKeyException : public NewException
	{
	public :
		BadChannelKeyException(std::string tag);
		virtual ~BadChannelKeyException() throw();
		virtual std::string	what() const throw();
	private :
		BadChannelKeyException();
		const std::string mTag;
	};
	// constructor && destructor
	Channel(const std::string &tag, const Client &channelCreater);
	Channel();
	~Channel();

	/* public member function */
	// set channel key
	void				setChannelKey(const std::string &channelKey);
	// set channel key
	// remove one in channel
	void	RemoveOne(const Client &target);
	// demote operator to user
	void	DemoteOperator(const Client &oper);
	// add user in channel
	void	AddUser(const Client &user) throw(Channel::BadChannelKeyException);
	// add operator in channel
	void	AddOperator(const Client &oper);
	// add user with key
	void	AddUserWithKey(const Client &user, const std::string &key) \
		throw(Channel::BadChannelKeyException);

	// broadcast sent back msg of command to all in channel
	void	SendBackCmdMsg(const std::string &cmdMsg);
	// broadcast private message to channel except broadcaster
	void	SendPrivateMsgToChannel(const Client &broadcaster, const std::string &msg);
private:

	/* private member function */
	// get operator location in vector
	std::vector<unsigned int>::iterator		getOperatorIter(const Client &target);
	// get user location in vector
	std::vector<const Client *>::iterator	getUserIter(const Client &target);

	/* private member variable */
	std::string					mTag;
	std::vector<unsigned int>	mOperators;
	std::vector<const Client *>	mUsers;
	std::string					mKey;
};
