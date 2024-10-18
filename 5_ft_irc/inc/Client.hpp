#pragma once

#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>

#include "Message.hpp"

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
	// setter
	void				SetNickName(const std::string &nickName);
	void				SetUserName(const std::string &userName);
	void				SetFd(unsigned int fd);
	void				SetHostName(const std::string &hostName);
	void				SetIpAddress(in_addr_t ipAddress);
	//MessageBuffer
	void				AddBuffer(const std::string buff);

private:
	// must not be call with default constructor(instance need ip info)
	Client();
	//MessageBuffer
	bool				checkCommand() const;
	AMessage*			makeCommand();

	// private member variable
	std::string		mNickName;
	std::string		mUserName;
	unsigned int	mFd;
	std::string		mHostName;
	in_addr_t		mIpAddress;
	std::string		mbuffer;
};
