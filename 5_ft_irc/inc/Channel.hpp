#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>

#include "Client.hpp"
#include "NewException.hpp"
#include "Server.hpp"
#include "ReplyMacros.hpp"

/*
		Channel mode

|	t	|	l	|	k	|	i	|
|	3	|	2	|	1	|	0	|

t is none
l is mLimit
k is mKey
i is mInviteLists

*/

# define I_MODE	(0)
# define K_MODE	(1)
# define L_MODE	(2)
# define T_MODE	(3)

# define LIMIT_OFF (-1)

# define TURN_OFF (false)
# define TURN_ON (true)

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
	bool	IsOperator(const Client	&target);
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

	// invite one in channel
	void	InviteOne(const Client *target);
	
	// find one in channel with nickname
	const Client	*FindUserInChannelWithNick(const std::string &nickname) const;
	const Client	*FindOpInChannelWithNick(const std::string &nickname) const;

	std::vector<const Client *>	&GetUserList();
	int		GetAllModeStatus() const;
	bool	GetOneModeStatus(int mode) const;
	bool	ToggleModeStatus(int mode, bool turn);
  const Client*		FindUser(const std::string& nick);
  
  	const std::string&	GetKey() const;
	void				SetKey(const std::string& key);
	int					GetLimit() const;
	void				SetLimit(int limit);
	const std::string&	GetTopic() const;
	void				SetTopic(const std::string& topic);

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
	//TODO : mInviteLists에 클라이언트가 도중에 나가면 해당 포인터는 어떻게 처리할 것인지
	//		1. 나갈 때 직접 찾아서 지우기
	//		2. 스마트 포인터..
	std::string					mTag;
	std::vector<unsigned int>	mOperators;
	std::vector<const Client *>	mUsers;
	std::vector<const Client *> mInviteLists;
	std::string					mKey;
	std::string					mTopic;
	int							mLimit;
	int							mMode;
};
