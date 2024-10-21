#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <cerrno>
#include "Client.hpp"

//TODO : 매크로 따로 옮기고 사이즈 설정 해야 함! 
# define LISTEN_SIZE (5)
# define EPOLL_SIZE (5)
# define BUF_SIZE (600)

//싱글톤 패턴
class Server
{
public:
	static Server* GetServer();
	void InitServer(const char* port);
	void ExecServerLoop(void);

private:
	static	Server* mInstance;
	struct	epoll_event *mEpollEvents;
	char	mBuffer[BUF_SIZE];
	int		mEpfd;
	int		mSocket;
	
	std::map<const int, Client> mClientMap;
	std::vector<int> mSendList;
	//server name
	//password
	//map<tag, <channel>>
	Server();
	void registerClient();
	int	 receiveFromClient(const int client_fd);
	void sendToClient(const int client_fd);
	void controlClientEvent(const int client_fd, const int epoll_mode, const int event_mode);
	void unregisterClientSocket(const int client_fd, const std::string& msg);
};
