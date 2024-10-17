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

	// public member function(remove one in channel)
	void	removeOne(const Client &target);
private:
	// must not be called with default variable(instance need creater info)
	Channel();

	// private member variable
	std::string					mTag;
	std::vector<unsigned int>	mOperators;
	std::vector<const Client *>	mUsers;
};
