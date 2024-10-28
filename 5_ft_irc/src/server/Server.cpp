#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include "Server.hpp"
#include "AMessage.hpp"

Server* Server::mInstance = NULL;

Server::Server()
	: mName("unlucky_DISCORD")
	, mPrefix(":unlucky_DISCORD ")
{
	std::cout << "Server Init" << std::endl;
}

Server::~Server()
{
}

Server* Server::GetServer()
{
	if (mInstance == NULL)
	{
		mInstance = new Server();
	}
	return (mInstance);
}

std::map<const int, Client>* Server::GetClientMap()
{
	return (&mClientMap);
}

const std::string&	Server::GetName() const
{
	return (mName);
}

const std::string&	Server::GetPassword() const
{
	return (mPassword);
}

void Server::SetNameAndPrefix(const std::string& name)
{
	mName = name;
	mPrefix = ":" + name + " ";
}

void Server::setPassword(const std::string& pass)
{
	mPassword = pass;
}

const std::string&	Server::GetPrefix() const
{
	return (mPrefix);
}

bool Server::InitServer(const char *port, const char* pass)
{
	struct sockaddr_in	address;

	setPassword(pass);
	mSocket = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(atoi(port));
	if (bind(mSocket, reinterpret_cast<sockaddr *>(& address), sizeof(address)) == -1)
	{
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return (false);
	}
	if (listen(mSocket, LISTEN_SIZE) == -1)
	{
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return (false);
	}
	mEpfd = epoll_create(EPOLL_SIZE);
	controlClientEvent(mSocket, EPOLL_CTL_ADD, EPOLLIN);
	return (true);
}

void Server::ExecServerLoop(void)
{
	int	event_count;
	int	i_event;
	int	client_fd;

	while (true)
	{
		event_count = epoll_wait(mEpfd, mEpollEvents, EPOLL_SIZE, -1);
		if (event_count == -1)
		{
			std::cerr << "Error: " << strerror(errno) << std::endl;
			break ;
		}
		for (i_event = 0; i_event < event_count; i_event++)
		{
			client_fd = mEpollEvents[i_event].data.fd;
			if (client_fd == mSocket)
			{
				registerClient();
			}
			else
			{
				receiveFromClientLoop(client_fd);
			}
		}
	}
	for (std::map<const int, Client>::iterator it = mClientMap.begin(); it != mClientMap.end(); ++it)
	{
		close(it->first);
	}
	close(mSocket);
	close(mEpfd);
}

std::map<const std::string, Channel>	&Server::GetChannelList()
{
	return (mChannelMap);
}

bool Server::registerClient()
{
	socklen_t			address_size;
	int					socket;
	struct sockaddr_in	address;

	address_size = sizeof(address);
	socket = accept(mSocket, reinterpret_cast<sockaddr *>(& address), &address_size);
	if (socket == -1)
	{
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return (false);
	}
	controlClientEvent(socket, EPOLL_CTL_ADD, EPOLLIN | EPOLLET);
	mClientMap.insert(std::make_pair(socket, Client(socket, address)));
	std::cerr << socket << " | " << ntohs(address.sin_port) << " connected."<< std::endl;
	return (true);
}

void Server::receiveFromClientLoop(int client_fd)
{
	while (true)
	{
		if (receiveFromClient(client_fd) == -1)
		{
			break ;
		}
	}
}

int Server::receiveFromClient(const int client_fd)
{
	int	len_buf;

	memset(mBuffer, 0, sizeof(mBuffer));
	len_buf = recv(client_fd, mBuffer, BUF_SIZE, MSG_DONTWAIT);
	if (len_buf == -1)
	{
		if (errno == EAGAIN)
		{
			return (-1);
		}
	}
	else if (len_buf == 0)
	{
		unregisterClientSocket(client_fd, " closed.");
		return (-1);
	}
	else
	{
		Client	*client = ReturnClientOrNull(client_fd);
		client->AddBuffer(mBuffer);
		if (client->CheckQuitFlag() == true)
		{
			unregisterClientSocket(client_fd, " closed.");
			return (-1);
		}
	}
	return (0);
}

void Server::controlClientEvent(const int client_fd, const int epoll_mode, const int event_mode)
{
	struct epoll_event	event;

	event.events = event_mode;
	event.data.fd = client_fd;
	epoll_ctl(mEpfd, epoll_mode, client_fd, &event);
}

void Server::unregisterClientSocket(const int client_fd, const std::string& msg)
{
	std::cerr << client_fd << msg << std::endl;
	epoll_ctl(mEpfd, EPOLL_CTL_DEL, client_fd, NULL);
	Client	&client = mClientMap.find(client_fd)->second;
	if (client.howManyChannelJoining() > 0)
	{
		std::vector<Channel *>				&channal_list = client.GetChannelListOfClient();
		std::vector<Channel *>::iterator	it = channal_list.begin();
		for (; it != channal_list.end(); ++it)
		{
			(*it)->ExcludeOneFromInvitation(&client);
			(*it)->RemoveOne(client);
		}
	}
	mClientMap.erase(client_fd);
	close(client_fd);
}

void Server::SendMessage(const Client &target, const std::string& msg)
{
	send(target.GetFd(), msg.c_str(), msg.size(), MSG_DONTWAIT);
}

Client*	Server::ReturnClientOrNull(const int fd)
{
	std::map<int, Client>::iterator it = mClientMap.find(fd);

	if (it == mClientMap.end())
	{
		return (NULL);
	}
	return (&(mClientMap.find(fd)->second));
}

Client*	Server::ReturnClientOrNull(const std::string& nick)
{
	std::map<const int, Client>::iterator it = mClientMap.begin();

	for (; it != mClientMap.end(); ++it)
	{
		if (it->second.GetNickName() == nick)
		{
			return (&(it->second));
		}
	}
	return (NULL);
}
