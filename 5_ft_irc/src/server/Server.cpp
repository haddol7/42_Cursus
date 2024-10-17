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
	struct epoll_event	event;
	
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
	event.data.fd = mSocket;
	event.events = EPOLLIN | EPOLLET;
	epoll_ctl(mEpfd, EPOLL_CTL_ADD, mSocket, &event);
}

void Server::ExecServerLoop(void)
{
	int		event_count;
	int		i_event;

	while (true)
	{
		event_count = epoll_wait(mEpfd, mEpollEvents, EPOLL_SIZE, -1);
		if (event_count == -1)
		{ 
			//error here
		}
		for (i_event = 0; i_event < event_count; i_event++)
		{
			if (mEpollEvents[i_event].data.fd == mSocket)
			{
				registerClient();
			}
			else
			{
				readBufferFromClientLoop(i_event);
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
	event.events = EPOLLIN | EPOLLET;
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

void Server::readBufferFromClientLoop(const int i_event)
{
	static char	buf[BUF_SIZE];
	int			len_buf;

	memset(buf, 0, sizeof(buf));
	while (true)
	{
		len_buf = read(mEpollEvents[i_event].data.fd, buf, BUF_SIZE);
		if (len_buf == 0)
		{
			epoll_ctl(mEpfd, EPOLL_CTL_DEL, mEpollEvents[i_event].data.fd, NULL);
			close(mEpollEvents[i_event].data.fd);
			break;
		}
		else if (len_buf < 0)
		{
			if (errno == EAGAIN)
			{
				break ;
			}
		}
		else
		{
			//test for broadcasting
			for (std::vector<int>::iterator it = test_ClientFd.begin() ; it != test_ClientFd.end(); ++it)
			{
				if (*it != mEpollEvents[i_event].data.fd)
				{
					write(*it, buf, len_buf);
				}
			}
		}
	}	
}
