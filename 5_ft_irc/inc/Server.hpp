#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>

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
	void ExecLoopServer(void);
	void CloseServerFd();

private:
	static Server* mInstance;
	int	mEpfd;
	struct epoll_event *mEpollEvents;
	
	int mSocket;
	//server name
	//password
	//map<nick <client>>
	//map<tag, <channel>>
	Server();
};
