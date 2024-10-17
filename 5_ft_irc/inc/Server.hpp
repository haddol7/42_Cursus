#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <vector>

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
	static Server* mInstance;
	struct epoll_event *mEpollEvents;
	int	mEpfd;
	int mSocket;
	
	//server name
	//password
	//map<nick <client>>
	//map<tag, <channel>>
	Server();
	void registerClient();
	void readBufferFromClientLoop(const int i_event);

	std::vector<int> test_ClientFd;
};
