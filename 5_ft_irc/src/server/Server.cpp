#include <iostream>
#include <cerrno>
#include <cstdio>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include "Server.hpp"

Server* Server::mInstance = NULL;

Server::Server()
{
	std::cout << "Server Init" << std::endl;
	test_ClientFd.reserve(100);
}

Server* Server::GetServer()
{
	if (mInstance == NULL)
	{
		mInstance = new Server();
	}
	return (mInstance);
}

//Init Server : make server listen to client socket and create epoll instance
void Server::InitServer(const char *port)
{
	struct sockaddr_in	address;
	
	mSocket = socket(PF_INET, SOCK_STREAM, 0);
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(atoi(port));

	if (bind(mSocket, reinterpret_cast<sockaddr *>(& address), sizeof(address)) == -1)
	{
		//error here
	}
	if (listen(mSocket, LISTEN_SIZE) == -1)
	{
		//error here
	}

	mEpfd = epoll_create(EPOLL_SIZE);
	mEpollEvents = new struct epoll_event[EPOLL_SIZE];
	controlClientEvent(mSocket, EPOLL_CTL_ADD, EPOLLIN);
}

void Server::ExecServerLoop(void)
{
	int	event_count;
	int	i_event;
	int	client_fd;
	int epoll_mode;

	while (true)
	{
		event_count = epoll_wait(mEpfd, mEpollEvents, EPOLL_SIZE, -1);
		if (event_count == -1)
		{ 
			//error here
		}
		for (i_event = 0; i_event < event_count; i_event++)
		{
			client_fd = mEpollEvents[i_event].data.fd;
			epoll_mode = mEpollEvents[i_event].events;
			if (client_fd == mSocket)
			{
				registerClient();
			}
			else if (epoll_mode & EPOLLIN)
			{
				readBufferFromClient(client_fd);
			}
			else if (epoll_mode & EPOLLOUT)
			{
				writeBuffertoClient(client_fd);
			}
		}
	}
	close(mSocket);
	close(mEpfd);
}

void Server::registerClient()
{	
	struct epoll_event	event;
	socklen_t			address_size;
	int					socket;
	struct sockaddr_in	address;

	address_size = sizeof(address);
	socket = accept(mSocket, reinterpret_cast<sockaddr *>(& address), &address_size);

	event.data.fd = socket;
	event.events = EPOLLIN;
	epoll_ctl(mEpfd, EPOLL_CTL_ADD, socket, &event);

	// ###### Add client class here! #########
	
	//test code
	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(address.sin_addr), ip_str, sizeof(ip_str));
	std::cout << "IP Address: " << ip_str << std::endl;
	std::cout << "Port: " << ntohs(address.sin_port) << std::endl;
	//test for broadcasting
	test_ClientFd.push_back(socket);
}

void Server::readBufferFromClient(const int client_fd)
{
	int			len_buf;

	memset(mBuffer, 0, sizeof(mBuffer));
	len_buf = read(client_fd, mBuffer, BUF_SIZE);
	if (len_buf == -1)
	{
		std::cerr << "readBufferFromClient : read error" << std::endl;
		epoll_ctl(mEpfd, EPOLL_CTL_DEL, client_fd, NULL);
		close(client_fd);
	}
	else if (len_buf == 0)
	{
		std::cerr << "client closed" << std::endl;
		epoll_ctl(mEpfd, EPOLL_CTL_DEL, client_fd, NULL);
		close(client_fd);
	}
	else
	{
		controlClientEvent(client_fd, EPOLL_CTL_MOD, EPOLLOUT);
		//test for broadcasting
		for (std::vector<int>::iterator it = test_ClientFd.begin() ; it != test_ClientFd.end(); ++it)
		{
			if (*it != client_fd)
			{
				write(*it, mBuffer, len_buf);
			}
		}
	}
}

void Server::writeBuffertoClient(const int client_fd)
{
	int	len_buf;

	len_buf = write(client_fd, mBuffer, strlen(mBuffer));
	if (len_buf == -1)
	{
		std::cerr << "writeBuffertoClient : write" << std::endl; 
		epoll_ctl(mEpfd, EPOLL_CTL_DEL, client_fd, NULL);
	}
	else
	{
		controlClientEvent(client_fd, EPOLL_CTL_MOD, EPOLLIN);
	}
	memset(mBuffer, 0, sizeof(mBuffer));
}

void Server::controlClientEvent(const int client_fd, const int epoll_mode, const int mode)
{
	struct epoll_event	ev;

	ev.events = mode;
	ev.data.fd = client_fd;
	epoll_ctl(mEpfd, epoll_mode, client_fd, &ev);
}
