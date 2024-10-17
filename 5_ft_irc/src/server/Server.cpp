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
	
	mSocket = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
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
	event.events = EPOLLIN;
	event.data.fd = mSocket;
	epoll_ctl(mEpfd, EPOLL_CTL_ADD, mSocket, &event);
}

void Server::ExecLoopServer(void)
{
	struct epoll_event	event;
	struct sockaddr_in	client_address;
	socklen_t			address_size;
	int					event_count;
	int					i_event;
	int					client_sock;
	int					str_len;


	char buf[BUF_SIZE];

	while (true)
	{	
		//TODO : -1 is blocking, 0 is non-blocking. choose until done!
		event_count = epoll_wait(mEpfd, mEpollEvents, EPOLL_SIZE, -1);
		if (event_count == -1)
		{
			//error here
		}
		for (i_event = 0; i_event < event_count; i_event++)
		{
			if (mEpollEvents[i_event].data.fd == mSocket)
			{
				address_size = sizeof(client_address);
				client_sock = accept(mSocket, reinterpret_cast<sockaddr *>(& client_address), &address_size);
				event.events = EPOLLIN | EPOLLET;
				event.data.fd = client_sock;
				epoll_ctl(mEpfd, EPOLL_CTL_ADD, client_sock, &event);
				
				char ip_str[INET_ADDRSTRLEN]; // IPv4 주소를 위한 문자열 공간
    			inet_ntop(AF_INET, &(client_address.sin_addr), ip_str, sizeof(ip_str)); // IP 주소 변환

    			std::cout << "Client connected:" << std::endl;
    			std::cout << "IP Address: " << ip_str << std::endl;
    			std::cout << "Port: " << ntohs(client_address.sin_port) << std::endl; // 포트 번호 변환
				
				//add client class
			}
			else
			{
				while (true)
				{
					str_len = read(mEpollEvents[i_event].data.fd, buf, BUF_SIZE);
					if (str_len == 0)
					{
						epoll_ctl(mEpfd, EPOLL_CTL_DEL, mEpollEvents[i_event].data.fd, NULL);
						close(mEpollEvents[i_event].data.fd);

						std::cout << "closed client" << mEpollEvents[i_event].data.fd;
						break;
					}
					else if (str_len == -1)
					{
						if (errno == EAGAIN)
						{
							break ;
						}
					}
					else
					{
						write(mEpollEvents[i_event].data.fd, buf, str_len);
						write(1, buf, str_len);
					}
				}
			}
		}
	}
	close(mSocket);
	close(mEpfd);
}


