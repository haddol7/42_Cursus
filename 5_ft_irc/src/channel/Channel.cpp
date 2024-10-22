#include "Channel.hpp"

// exception class function
Channel::BadChannelKeyException::BadChannelKeyException(const std::string &tag) \
	: mTag(tag) {}

Channel::BadChannelKeyException::~BadChannelKeyException() throw() {}

const char	*Channel::BadChannelKeyException::what() const throw()
{
	return (ERR_BADCHANNELKEY(mTag).c_str());
}

// constructor && destructor
Channel::Channel(const std::string &tag, const Client &channelCreater) \
	: mTag(tag), \
	mKey("")
{
	mOperators.reserve(10);
	mUsers.reserve(50);
	AddOperator(channelCreater);
	AddUser(channelCreater);
}

Channel::~Channel(){}

/* public member function */
// set channel key
void				Channel::setChannelKey(const std::string &channelKey)
{
	mKey = channelKey;	
}

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
void	Channel::AddUser(const Client &user) throw(Channel::BadChannelKeyException)
{
	// key가 할당되어 있는 상황에서는 key 없이 channel에 들어올 수 없다.
	if (mKey != std::string(""))
		throw (BadChannelKeyException(mTag));
	if (getUserIter(user) != mUsers.end())
		return ;
	
	mUsers.push_back(&user);
}

// add operator in channel
void	Channel::AddOperator(const Client &oper)
{
	if (getOperatorIter(oper) != mOperators.end())
		return ;
	
	mOperators.push_back(oper.GetFd());
}

// add user with key
void	Channel::AddUserWithKey(const Client &user, const std::string &key) \
	throw(Channel::BadChannelKeyException)
{
	if (key != mKey && !mKey.empty())
		throw (BadChannelKeyException(mTag));
	if (getUserIter(user) != mUsers.end())
		return ;
	
	mUsers.push_back(&user);
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
		
		Server::GetServer()->SendMessage(const_cast<Client &>(broadcaster), msg);
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
