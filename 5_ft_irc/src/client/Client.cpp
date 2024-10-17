#include "Client.hpp"

// constructor && destructor
Client::Client(unsigned int fd, sockaddr_in clientAddrInfo) \
	: mFd(fd), \
	mIpAddress(clientAddrInfo.sin_addr.s_addr) \
{
	struct hostent	*host;

	host = gethostbyaddr(reinterpret_cast<char *>(&clientAddrInfo), 4, AF_INET);
	if (host)
		mHostName = host->h_name;
}

Client::~Client() {}

// public member function(getter)

const std::string	&Client::GetNickName() const
{
	return (mNickName);
}

const std::string	&Client::GetUserName() const
{
	return (mUserName);
}

unsigned int		Client::GetFd() const
{
	return (mFd);
}

const std::string	&Client::GetHostName() const
{
	return (mHostName);
}

in_addr_t			Client::GetIpAddress() const
{
	return (mIpAddress);	
}

// public member function(setter)

void				Client::SetNickName(const std::string &_nickName)
{
	mNickName = _nickName;
}

void				Client::SetUserName(const std::string &_userName)
{
	mUserName = _userName;
}

void				Client::SetFd(unsigned int _fd)
{
	mFd = _fd;
}

void				Client::SetHostName(const std::string &_hostName)
{
	mHostName = _hostName;
}

void				Client::SetIpAddress(in_addr_t _ipAddress)
{
	mIpAddress = _ipAddress;
}