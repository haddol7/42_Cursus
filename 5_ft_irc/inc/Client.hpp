#pragma once

#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>

#include "message.hpp"

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
	unsigned int		GetFd() const;
	const std::string&	GetHostName() const;
	in_addr_t			GetIpAddress() const;
	const std::string&	GetIpAddressString() const;
	bool				GetPasswordConfirmation() const;
	int					GetRegisterStatus() const;
	// setter
	void				SetNickName(const std::string &nickName);
	void				SetUserName(const std::string &userName);
	void				SetHostName(const std::string &hostName);
	void				SetPasswordConfirmation(const bool passwordConfirmation);
	//MessageBuffer
	void				AddBuffer(const std::string &buff);
	void				TurnOnRegisterStatus(int mode);

private:
	// must not be call with default constructor(instance need ip info)
	//MessageBuffer
	bool				checkCommand() const;
	AMessage*			makeCommand();

	// private member variable
	const unsigned int	mFd;
	const in_addr_t		mIpAddress;
	std::string			mIpAddressString;
	std::string			mHostName;
	std::string			mNickName;
	std::string			mUserName;
	bool				mPasswordConfirmation;
	int					mRegisterStatus;
	std::string			mbuffer;
};
