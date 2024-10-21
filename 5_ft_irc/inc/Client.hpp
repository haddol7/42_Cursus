#pragma once

#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>

#include "message.hpp"

class Client
{
public:
	// constructor && destructor
	Client(unsigned int fd, sockaddr_in clientAddrInfo);
	~Client();

	// getter
	const std::string&	GetNickName() const;
	const std::string&	GetUserName() const;
	unsigned int		GetFd() const;
	const std::string&	GetHostName() const;
	in_addr_t			GetIpAddress() const;
	bool				GetPasswordConfirmation() const;
	// setter
	void				SetNickName(const std::string &nickName);
	void				SetUserName(const std::string &userName);
	void				SetHostName(const std::string &hostName);
	void				SetPasswordConfirmation(const bool passwordConfirmation);
	//MessageBuffer
	void				AddBuffer(const std::string buff);

private:
	// must not be call with default constructor(instance need ip info)
	Client();
	//MessageBuffer
	bool				checkCommand() const;
	AMessage*			makeCommand();

	// private member variable
	const unsigned int	mFd;
	const in_addr_t		mIpAddress;
	std::string			mHostName;
	std::string			mNickName;
	std::string			mUserName;
	bool				mPasswordConfirmation;
	std::string			mbuffer;
};
