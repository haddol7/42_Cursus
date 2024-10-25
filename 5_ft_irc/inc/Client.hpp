#pragma once

#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <vector>

#include "message.hpp"
#include "Channel.hpp"

//Client RegisterStatus Bitmask
//	 | USER | NICK | PASS |

# define REGISTERD (7)
# define PASS (0)
# define NICK (1)
# define USER (2)

class Client
{
public:
	// constructor && destructor
	Client(unsigned int fd, sockaddr_in clientAddrInfo);
	Client();
	~Client();

	// getter
	const std::string&	GetNickName() const;
	const std::string&	GetUserName() const;
	const std::string&	GetHostName() const;
	const std::string&	GetServerName() const;
	const std::string&	GetRealName() const;
	std::string			GetClientPrefix() const;
	unsigned int		GetFd() const;
	in_addr_t			GetIpAddress() const;
	const std::string&	GetIpAddressString() const;
	bool				GetPasswordConfirmation() const;
	int					GetRegisterStatus() const;
	// setter
	void				SetNickName(const std::string &nickName);
	void				SetUserName(const std::string &userName);
	void				SetHostName(const std::string &hostName);
	void				SetServerName(const std::string &serverName);
	void				SetRealName(const std::string &realName);
	void				SetPasswordConfirmation(const bool passwordConfirmation);
	//MessageBuffer
	void				AddBuffer(const std::string &buff);
	void				TurnOnRegisterStatus(int mode);
	void				TriggerQuitFlag();
	bool				CheckQuitFlag() const;
	void				JoinNewChannel(Channel *channel);
	void				PartChannel(Channel *channel);
	// 클라이언트가 가입 중인 채널 정보 가져오기
	int						howManyChannelJoining();
	std::vector<Channel *>	&GetChannelListOfClient();
	

	// 클라이언트가 가입할 수 있는 채널 개수의 상한값
	const static int	sMaximumChannelJoin = 10;

private:
	//MessageBuffer
	bool				checkCommand() const;
	AMessage*			makeCommand();
	// mChannelListOfClient 관리
	std::vector<Channel *>::iterator	GetChannelOfClientIter(const Channel *channel);

	// private member variable
	const unsigned int	mFd;
	const in_addr_t		mIpAddress;
	std::string			mIpAddressString;
	std::string			mNickName;
	std::string			mUserName;
	std::string			mHostName;
	std::string			mServerName;
	std::string			mRealName;
	bool				mPasswordConfirmation;
	bool				mQuitFlag;
	int					mRegisterStatus;
	std::string			mbuffer;
	
	// Client가 가입 중인 채널의 목록
	std::vector<Channel *>	mChannelListOfClient;
};
