#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include "Client.hpp"

class Channel
{
public:
	// constructor && destructor
	Channel(const std::string &tag, const Client &channelCreater);
	~Channel();

	/* public member function */
	// remove one in channel
	void	RemoveOne(const Client &target);
	// demote operator to user
	void	DemoteOperator(const Client &oper);
	// add user in channel
	void	AddUser(const Client &user);
	// add operator in channel
	void	AddOperator(const Client &oper);

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
};
