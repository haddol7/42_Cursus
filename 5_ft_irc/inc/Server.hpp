#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <cerrno>
#include "Client.hpp"

# define LISTEN_SIZE (5)
# define EPOLL_SIZE (5)
# define BUF_SIZE (600)

class Channel;

class Server
{
public:
	static	Server* 				GetServer();
	std::map<const int, Client>*	GetClientMap();
	const std::string&				GetName() const;
	const std::string&				GetPassword() const;
	const std::string&				GetPrefix() const;
	void							SetNameAndPrefix(const std::string& name);

	bool							InitServer(const char* port, const char* pass);
	void							ExecServerLoop(void);

	void							SendMessage(const Client &target, const std::string& msg);
	Client*							ReturnClientOrNull(const int fd);
	Client*							ReturnClientOrNull(const std::string& nick);

	std::map<const std::string, Channel>	&GetChannelList();

private:
	static Server					*mInstance;
	struct epoll_event				mEpollEvents[EPOLL_SIZE];
	std::string						mName;
	std::string						mPassword;
	std::string						mPrefix;
	char							mBuffer[BUF_SIZE];
	int								mEpfd;
	int								mSocket;
	std::map<const int, Client>		mClientMap;
	std::map<const std::string, Channel> mChannelMap;

	Server();
	~Server();
	void	setPassword(const std::string& pass);
	bool	registerClient();
	void	receiveFromClientLoop(const int client_fd);
	int		receiveFromClient(const int client_fd);
	void	controlClientEvent(const int client_fd, const int epoll_mode, const int event_mode);
	void	unregisterClientSocket(const int client_fd, const std::string& msg);
};

#include "Channel.hpp"
