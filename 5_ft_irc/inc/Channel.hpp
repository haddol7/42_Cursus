#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>

#include "Client.hpp"
#include "ReplyMacros.hpp"

class Channel
{
public:
	// exception class
	class BADCHANNELKEYEXCEPTION : std::exception
	{
	public :
		BADCHANNELKEYEXCEPTION(const std::string &tag);
		virtual const char	*what() const throw();
	private :
		BADCHANNELKEYEXCEPTION();
		const std::string mTag;
	};
	// constructor && destructor
	Channel(const std::string &tag, const Client &channelCreater);
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
	void	AddUser(const Client &user) throw(Channel::BADCHANNELKEYEXCEPTION);
	// add operator in channel
	void	AddOperator(const Client &oper);
	// add user with key
	void	AddUserWithKey(const Client &user, const std::string &key) \
		throw(Channel::BADCHANNELKEYEXCEPTION);

	// broadcast message to channel
	void	Broadcast(const Client &broadcaster, const std::string &msg);

private:
	// must not be called with default variable(instance need creater info)
	Channel();

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
