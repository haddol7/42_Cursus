#include "Channel.hpp"

// exception class function
Channel::BadChannelKeyException::BadChannelKeyException(std::string tag) \
	: mTag(tag) {}

Channel::BadChannelKeyException::~BadChannelKeyException() throw() {}

std::string	Channel::BadChannelKeyException::what() const throw()
{
	return (ERR_BADCHANNELKEY(mTag).c_str());
}

// constructor && destructor
Channel::Channel(const std::string &tag, const Client &channelCreater) \
	: mTag(tag), \
	mKey(""),
	mLimit(LIMIT_OFF),
	mMode(0)
{
	mOperators.reserve(10);
	mInviteLists.reserve(50);
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
	if (!mKey.empty())
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

// invite one in channel
void	Channel::InviteOne(const Client *target)
{
	// 이미 초대 리스트에 있으면 아무런 동작도 하지 않고 넘김
	std::vector<const Client *>::iterator iter = mInviteLists.begin();
	for (; iter != mInviteLists.end(); iter++)
	{
		if (*iter == target)
			return ;
	}
	mInviteLists.push_back(target);
}

// find one in channel with nickname
const Client	*Channel::FindUserInChannelWithNick(const std::string &nickname) const
{
	for (std::vector<const Client *>::const_iterator i = mUsers.begin(); \
		i != mUsers.end(); i++)
	{
		if ((*i)->GetNickName() == nickname)
			return (*i);
	}
	return (NULL);
}
const Client	*Channel::FindOpInChannelWithNick(const std::string &nickname) const
{
	for (std::vector<unsigned int>::const_iterator i = mOperators.begin(); \
		i != mOperators.end(); i++)
	{
		for (std::vector<const Client *>::const_iterator j = mUsers.begin(); \
			j != mUsers.end(); j++)
		{
			if ((*j)->GetFd() == (*i))
			{
				if ((*j)->GetNickName() == nickname)
					return (*j);
			}
		}
	}
	return (NULL);
}

// broadcast sent back msg of command to all in channel
void	Channel::SendBackCmdMsg(const std::string &cmdMsg)
{
	for (std::vector<const Client *>::iterator iter = mUsers.begin(); \
		iter != mUsers.end(); iter++)
		Server::GetServer()->SendMessage(const_cast<Client &>(**iter), cmdMsg);
}

// broadcast private message to channel except broadcaster
void	Channel::SendPrivateMsgToChannel(const Client &broadcaster, const std::string &msg)
{
	for (std::vector<const Client *>::iterator iter = mUsers.begin(); \
		iter != mUsers.end(); iter++)
	{
		if (*iter == &broadcaster)
			continue ;
		Server::GetServer()->SendMessage(const_cast<Client &>(**iter), msg);
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
	return (std::find(mUsers.begin(), mUsers.end(), &target));
}

int		Channel::GetAllModeStatus()
{
	return (mMode);
}

bool	Channel::GetOneModeStatus(int mode) const
{
	if (mode < I_MODE || mode > T_MODE)
	{
		return (false);
	}
	return (mMode & (1 << mode));
}

//반환값은 모드를 바꿨으면 true, 그렇지 못하면 false입니다.
bool	Channel::ToggleModeStatus(int mode, bool turn)
{
	if (mode < I_MODE || mode > T_MODE || GetOneModeStatus(mode) == turn)
	{
		return (false);
	}
	if (turn == TURN_ON)
	{
		mMode = mMode | (1 << mode);
	}
	else
	{
		mMode = mMode & ~(1 << mode);
	}
	return (true);
}
