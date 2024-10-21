#include "Client.hpp"

// constructor && destructor
Client::Client(unsigned int fd, sockaddr_in clientAddrInfo) \
	: mFd(fd), \
	mIpAddress(clientAddrInfo.sin_addr.s_addr), \
	mPasswordConfirmation(false) \
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

bool				Client::GetPasswordConfirmation() const
{
	return (mPasswordConfirmation);
}

// public member function(setter)

void				Client::SetNickName(const std::string &nickName)
{
	mNickName = nickName;
}

void				Client::SetUserName(const std::string &userName)
{
	mUserName = userName;
}

void				Client::SetHostName(const std::string &hostName)
{
	mHostName = hostName;
}

void				Client::SetPasswordConfirmation(const bool passwordConfirmation)
{
	mPasswordConfirmation = passwordConfirmation;
}

void	Client::AddBuffer(const std::string buff)
{
	mbuffer = mbuffer + buff;

	AMessage*	message;

	while (checkCommand())
	{
		message = makeCommand();
		message->ExecuteCommand();
		delete message;
	}
}

bool	Client::checkCommand() const
{
	size_t	length;

	length = mbuffer.length();
	if (length >= 512)
		return 1;
	else if (mbuffer.find("\r\n") != std::string::npos)
		return 1;
	return 0;
}

AMessage*	Client::makeCommand()
{
	size_t		length;
	char		buff[513];
	AMessage*	message;

	length = mbuffer.length();
	if (length >= 512)
	{
		mbuffer.copy(buff, 512, 0);
		buff[510] = '\r';
		buff[511] = '\n';
		buff[512] = '\0';
	}
	else
	{
		std::string::size_type	pos = mbuffer.find("\r\n");
		mbuffer.copy(buff, pos + 2, 0);
		mbuffer.erase(0, pos + 2);
		buff[pos + 2] = '\0';
	}
	message = AMessage::GetMessageObject(mNickName, buff);
	return message;
}
