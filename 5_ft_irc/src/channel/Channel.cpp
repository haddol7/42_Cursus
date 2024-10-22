#include "Channel.hpp"

// constructor && destructor
Channel::Channel(const std::string &tag, const Client &channelCreater) \
	: mTag(tag) \
{
	mOperators.reserve(10);
	mUsers.reserve(50);
	AddOperator(channelCreater);
	AddUser(channelCreater);
}

Channel::~Channel(){}

/* public member function */
// remove one in channel
void	Channel::RemoveOne(const Client &target)
{
	DemoteOperator(target);
	
	std::vector<const Client *>::iterator	targetLocation = \
		getUserIter(target);

	if (targetLocation == mUsers.end())
		return ;
	else
		mUsers.erase(targetLocation);
}

// demote operator to user
void	Channel::DemoteOperator(const Client &target)
{
	std::vector<unsigned int>::iterator	targetLocation = \
		getOperatorIter(target);

	if (targetLocation == mOperators.end())
		return ;
	else
		mOperators.erase(targetLocation);
}

// add user in channel
void	Channel::AddUser(const Client &user)
{	
	if (getUserIter(user) == mUsers.end())
		return ;
	
	mUsers.push_back(&user);
}

// add operator in channel
void	Channel::AddOperator(const Client &oper)
{
	if (getOperatorIter(oper) == mOperators.end())
		return ;
	
	mOperators.push_back(oper.GetFd());
}

// broadcast message to channel
// TODO : primsg의 파라미터로 채널이 왔을 때 이 함수를 사용하시면 됩니다.
void	Channel::Broadcast(const Client &broadcaster, const std::string &msg)
{
	for (std::vector<const Client *>::iterator iter = mUsers.begin(); \
		iter != mUsers.end(); iter++)
	{
		if (*iter == &broadcaster)
			continue ;
		
		if (send((*iter)->GetFd(), msg.c_str(), msg.size(), MSG_DONTWAIT) == -1)
			perror("send(at channel broadcast) error");
	}
}

// must not be called with default variable(instance need creater info)
Channel::Channel(){}

/* private member function */
// get operator location in vector
std::vector<unsigned int>::iterator		Channel::getOperatorIter(const Client &target)
{
	return (std::find(mOperators.begin(), mOperators.end(), target.GetFd()));
}

// get user location in vector
std::vector<const Client *>::iterator	Channel::getUserIter(const Client &target)
{
	return (std::find(mUsers.begin(), mUsers.begin(), &target));
}
