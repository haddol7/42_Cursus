#include "Channel.hpp"

// constructor && destructor
Channel::Channel(const std::string &tag, const Client &channelCreater) \
	: mTag(tag) \
{
	mOperators.push_back(channelCreater.GetFd());
	mUsers.push_back(&channelCreater);
}

Channel::~Channel(){}

// public member function(remove one in channel)
void	Channel::removeOne(const Client &target)
{
	std::vector<unsigned int>::iterator		cursorOperators = \
		std::find(mOperators.begin(), mOperators.end(), target.GetFd());
	std::vector<const Client *>::iterator	cursorUsers		= \
		std::find(mUsers.begin(), mUsers.end(), &target);
	
	if (cursorOperators == mOperators.end())
		return ;
	else
		mOperators.erase(cursorOperators);
	
	if (cursorUsers == mUsers.end())
		return ;
	else
		mUsers.erase(cursorUsers);
}

// must not be called with default variable(instance need creater info)
Channel::Channel(){}