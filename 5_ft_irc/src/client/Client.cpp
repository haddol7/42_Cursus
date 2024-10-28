#include "Client.hpp"

// constructor && destructor
Client::Client(unsigned int fd, sockaddr_in clientAddrInfo) \
	: mFd(fd), \
	mIpAddress(clientAddrInfo.sin_addr.s_addr), \
	mQuitFlag(false),
	mRegisterStatus(0)
{
	struct hostent	*host;

	mIpAddressString = inet_ntoa(clientAddrInfo.sin_addr);
	host = gethostbyaddr(&clientAddrInfo.sin_addr, sizeof(clientAddrInfo.sin_addr), AF_INET);
	if (host)
	{
		mHostName = host->h_name;
	}
	else
	{
		mHostName = "Unknownhost";
	}
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

const std::string	&Client::GetHostName() const
{
	return (mHostName);
}

const std::string	&Client::GetServerName() const
{
	return (mServerName);
}

const std::string	&Client::GetRealName() const
{
	return (mRealName);
}

std::string	Client::GetClientPrefix() const
{
	return mNickName + "!" + mUserName + "@" + mHostName + " ";
}

unsigned int		Client::GetFd() const
{
	return (mFd);
}

in_addr_t			Client::GetIpAddress() const
{
	return (mIpAddress);
}

const std::string&	Client::GetIpAddressString() const
{
	return (mIpAddressString);
}

int					Client::GetRegisterStatus() const
{
	return (mRegisterStatus);
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

void				Client::SetServerName(const std::string &serverName)
{
	mServerName = serverName;
}

void				Client::SetRealName(const std::string &realName)
{
	mRealName = realName;
}

void	Client::AddBuffer(const std::string& buff)
{
	//mbuffer = mbuffer + buff;
	mbuffer.append(buff);

	AMessage*	message;

	while (checkCommand() == true && CheckQuitFlag() == false)
	{
		message = makeCommand();
		if (message != NULL)
		{
			message->ExecuteCommand();
			delete message;
		}
	}
}

bool	Client::checkCommand() const
{
	size_t	length;

	length = mbuffer.length();
	if (length >= 512)
		return true;
	else if (mbuffer.find("\r\n") != std::string::npos)
		return true;
	return false;
}

AMessage*	Client::makeCommand()
{
	char		buff[513];
	AMessage*	message;

	std::string::size_type	pos = mbuffer.find("\r\n");
	if (pos >= 511)
	{
		mbuffer.copy(buff, 512, 0);
		mbuffer.erase(0, 512);
		buff[510] = '\r';
		buff[511] = '\n';
		buff[512] = '\0';
	}
	else
	{
		pos = pos + 2;
		mbuffer.copy(buff, pos, 0);
		mbuffer.erase(0, pos);
		buff[pos] = '\0';
	}
	message = AMessage::GetMessageObject(this, buff);
	return message;
}

void		Client::TurnOnRegisterStatus(int mode)
{
	if (mode < 0 || mode > 3 || GetRegisterStatus() & (1 << mode))
	{
		return ;
	}
	mRegisterStatus |= (1 << mode);
	if (GetRegisterStatus() == REGISTERD)
	{
		std::string	result;

		result = Server::GetServer()->GetPrefix() + RPL_WELCOME(GetNickName(), GetUserName(), GetHostName());
		Server::GetServer()->SendMessage(*this, result);
	}
}

void	Client::TriggerQuitFlag()
{
	mQuitFlag = true;
}

bool	Client::CheckQuitFlag() const
{
	return (mQuitFlag);
}

// mChannelListOfClient 관리
std::vector<Channel *>::iterator	Client::GetChannelOfClientIter(const Channel *channel)
{
	return (std::find(mChannelListOfClient.begin(), mChannelListOfClient.end(), channel));
}

void				Client::JoinNewChannel(Channel *channel)
{
	if (GetChannelOfClientIter(channel) != mChannelListOfClient.end())
	{
		return ;
	}
	mChannelListOfClient.push_back(channel);
}

void				Client::PartChannel(Channel *channel)
{
	std::vector<Channel *>::iterator	channelIter = GetChannelOfClientIter(channel);
	if (channelIter == mChannelListOfClient.end())
	{
		return ;
	}
	mChannelListOfClient.erase(channelIter);	
}

// 클라이언트가 가입 중인 채널 정보 가져오기
int						Client::howManyChannelJoining()
{
	return (mChannelListOfClient.size());
}

std::vector<Channel *>	&Client::GetChannelListOfClient()
{
	return (mChannelListOfClient);
}
